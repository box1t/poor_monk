#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <cuda_runtime.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define CSC(call)                                                       \
  do {                                                                         \
    cudaError_t _err = (call);                                                 \
    if (_err != cudaSuccess) {                                                 \
      fprintf(stderr, "ERROR in %s:%d: %s\n", __FILE__, __LINE__,         \
              cudaGetErrorString(_err));                                       \
      exit(0);                                                                 \
    }                                                                          \
  } while (0)

const int TRIANGLE_COUNT = 62;

struct Vec3 {
  double x, y, z;

  __host__ __device__ Vec3() : x(0.0), y(0.0), z(0.0) {}
  __host__ __device__ Vec3(double xx, double yy, double zz) : x(xx), y(yy), z(zz) {}
};

__host__ __device__ Vec3 operator+(const Vec3 &a, const Vec3 &b) {
  return Vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

__host__ __device__ Vec3 operator-(const Vec3 &a, const Vec3 &b) {
  return Vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

__host__ __device__ Vec3 operator*(const Vec3 &a, double s) {
  return Vec3(a.x * s, a.y * s, a.z * s);
}

struct Triangle {
  Vec3 a, b, c;
  uchar4 color;

  __host__ __device__ Triangle() {}
  __host__ __device__ Triangle(const Vec3 &aa, const Vec3 &bb, const Vec3 &cc, uchar4 col)
      : a(aa), b(bb), c(cc), color(col) {}
};

struct Scene {
  Triangle *tris;
  int       triCount;
  Vec3      lightPos;
  uchar4    lightColor;
};

struct Camera {
  Vec3 pos;
  Vec3 lookAt;
  double fovDeg;
};

__host__ __device__ inline double dot3(const Vec3 &a, const Vec3 &b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

__host__ __device__ inline Vec3 cross3(const Vec3 &a, const Vec3 &b) {
  return Vec3(
      a.y * b.z - a.z * b.y,
      a.z * b.x - a.x * b.z,
      a.x * b.y - a.y * b.x
  );
}

__host__ __device__ inline Vec3 normalize(const Vec3 &v) {
  double len = sqrt(dot3(v, v));
  return Vec3(v.x / len, v.y / len, v.z / len);
}

__host__ __device__ inline Vec3 basisMul(const Vec3 &ex, const Vec3 &ey, const Vec3 &ez,
                                         const Vec3 &v) {
  return Vec3(
      ex.x * v.x + ey.x * v.y + ez.x * v.z,
      ex.y * v.x + ey.y * v.y + ez.y * v.z,
      ex.z * v.x + ey.z * v.y + ez.z * v.z
  );
}

struct HitInfo {
  int   triIndex;
  double t;
};

__host__ __device__ bool intersectTriangle(const Vec3 &orig,
                                           const Vec3 &dir,
                                           const Triangle &tri,
                                           double &tOut) {
  const double EPS = 1e-10;
  Vec3 e1 = tri.b - tri.a;
  Vec3 e2 = tri.c - tri.a;
  Vec3 p = cross3(dir, e2);
  double det = dot3(p, e1);
  if (fabs(det) < EPS) return false;

  double invDet = 1.0 / det;
  Vec3 tvec = orig - tri.a;
  double u = dot3(p, tvec) * invDet;
  if (u < 0.0 || u > 1.0) return false;

  Vec3 q = cross3(tvec, e1);
  double v = dot3(q, dir) * invDet;
  if (v < 0.0 || u + v > 1.0) return false;

  double t = dot3(q, e2) * invDet;
  if (t < 0.0) return false;

  tOut = t;
  return true;
}

__host__ __device__ HitInfo tracePrimary(const Vec3 &orig,
                                         const Vec3 &dir,
                                         const Scene &scene) {
  HitInfo hit;
  hit.triIndex = -1;
  hit.t = 0.0;

  for (int i = 0; i < scene.triCount; ++i) {
    double tCandidate;
    if (!intersectTriangle(orig, dir, scene.tris[i], tCandidate)) continue;

    if (hit.triIndex < 0 || tCandidate < hit.t) {
      hit.triIndex = i;
      hit.t = tCandidate;
    }
  }
  return hit;
}

__host__ __device__ bool isShadowed(const Vec3 &point,
                                    const Vec3 &lightDir,
                                    double maxDist,
                                    const Scene &scene,
                                    int selfIndex) {
  for (int i = 0; i < scene.triCount; ++i) {
    if (i == selfIndex) continue;
    double tCandidate;
    if (!intersectTriangle(point, lightDir, scene.tris[i], tCandidate)) continue;
    if (tCandidate > 0.0 && tCandidate < maxDist) {
      return true;
    }
  }
  return false;
}

__host__ __device__ uchar4 shadeRay(const Vec3 &orig, const Vec3 &dir, const Scene &scene) {
  HitInfo h = tracePrimary(orig, dir, scene);
  
  if (h.triIndex < 0) {
    return make_uchar4(15, 20, 30, 255); 
  }

  Vec3 hitPos = orig + dir * h.t;
  Vec3 toLight = scene.lightPos - hitPos;
  double dist = sqrt(dot3(toLight, toLight));
  Vec3 lightDir = normalize(toLight);

  if (isShadowed(hitPos, lightDir, dist, scene, h.triIndex)) {
    const Triangle &tri = scene.tris[h.triIndex];
    return make_uchar4(tri.color.x * 0.3, tri.color.y * 0.3, tri.color.z * 0.3, 255);
  }

  const Triangle &tri = scene.tris[h.triIndex];
  return make_uchar4(
      (int)(tri.color.x * scene.lightColor.x),
      (int)(tri.color.y * scene.lightColor.y),
      (int)(tri.color.z * scene.lightColor.z),
      255
  );
}

__host__ __device__ void buildCameraBasis(const Camera &cam,
                                          Vec3 &ex, Vec3 &ey, Vec3 &ez) {
  ez = normalize(cam.lookAt - cam.pos);
  Vec3 worldUp(0.0, 0.0, 1.0);
  ex = normalize(cross3(ez, worldUp));
  ey = normalize(cross3(ex, ez));
}

__host__ __device__ uchar4 renderPixel(int px, int py,
                                       int width, int height,
                                       int sqrtSamples,
                                       const Camera &cam,
                                       const Scene &scene) {
  Vec3 ex, ey, ez;
  buildCameraBasis(cam, ex, ey, ez);

  float invW = 1.0f / (float)(width - 1.0);
  float invH = 1.0f / (float)(height - 1.0);
  float invS = 1.0f / (float)sqrtSamples;
  float aspect = (float)height * invW;
  
  float z = 1.0f / tanf(cam.fovDeg * (float)M_PI / 360.0f);

  uint4 acc = make_uint4(0, 0, 0, 0);
  int totalSamples = sqrtSamples * sqrtSamples;

  for (int sx = 0; sx < sqrtSamples; ++sx) {
    for (int sy = 0; sy < sqrtSamples; ++sy) {
      float u = ((px + (sx + 0.5f) * invS) * invW) * 2.0f - 1.0f;
      float v = ((py + (sy + 0.5f) * invS) * invH) * 2.0f - 1.0f;
      v *= aspect;

      Vec3 viewDirCam(u, v, z);
      Vec3 worldDir = normalize(basisMul(ex, ey, ez, viewDirCam));

      uchar4 c = shadeRay(cam.pos, worldDir, scene);
      acc.x += c.x;
      acc.y += c.y;
      acc.z += c.z;
    }
  }

  return make_uchar4(acc.x / totalSamples,
                     acc.y / totalSamples,
                     acc.z / totalSamples,
                     255);
}

void renderFrameCPU(const Camera &cam,
                    int width, int height,
                    int sqrtSamples,
                    const Scene &scene,
                    uchar4 *outImage) {
  for (int j = 0; j < height; ++j) {
    for (int i = 0; i < width; ++i) {
      int idx = (height - 1 - j) * width + i;
      outImage[idx] = renderPixel(i, j, width, height, sqrtSamples, cam, scene);
    }
  }
}

__global__ void renderKernel(const Camera cam,
                             int width, int height,
                             int sqrtSamples,
                             Scene scene,
                             uchar4 *outImage) {
    const int ix = blockIdx.x * blockDim.x + threadIdx.x;
    const int iy = blockIdx.y * blockDim.y + threadIdx.y;

    if (ix >= width || iy >= height) return;

    const int idx = (height - 1 - iy) * width + ix;

    outImage[idx] = renderPixel(ix, iy, width, height, sqrtSamples, cam, scene);
}

void buildFloor(const Vec3 &a, const Vec3 &b, const Vec3 &c, const Vec3 &d,
                uchar4 color, Triangle *tris, int offset) {
    
    tris[offset] = Triangle(a, b, c, color);
    
    tris[offset + 1] = Triangle(a, c, d, color);
    
}

void buildTetrahedron(const Vec3 &center,
                      double r,
                      uchar4 color,
                      Triangle *tris,
                      int offset) {
  double edge = r * sqrt(3.0);
  double stretch = 2.0;

  Vec3 v0(center.x - edge / 2.0, center.y - r * 0.3 * stretch, center.z - edge / sqrt(12.0));
  Vec3 v1(center.x,               center.y + r * stretch,      center.z - edge / sqrt(12.0));
  Vec3 v2(center.x + edge / 2.0, center.y - r * 0.3 * stretch, center.z - edge / sqrt(12.0));
  Vec3 v3(center.x,               center.y,                    center.z + r);

  tris[offset + 0] = Triangle(v0, v1, v2, color);
  tris[offset + 1] = Triangle(v0, v1, v3, color);
  tris[offset + 2] = Triangle(v0, v2, v3, color);
  tris[offset + 3] = Triangle(v1, v2, v3, color);
}

void buildIcosahedron(const Vec3 &center,
                      double r,
                      uchar4 color,
                      Triangle *tris,
                      int offset) {
    // Золотое сечение
    double phi = (1.0 + sqrt(5.0)) / 2.0;
    
    double norm = r / sqrt(1.0 + phi * phi);
    double h = 1.0 * norm;
    double w = phi * norm;

    Vec3 v[12] = {
        Vec3(center.x - h, center.y + w, center.z),     
        Vec3(center.x + h, center.y + w, center.z),     
        Vec3(center.x - h, center.y - w, center.z),     
        Vec3(center.x + h, center.y - w, center.z),     

        Vec3(center.x, center.y - h, center.z + w),     
        Vec3(center.x, center.y + h, center.z + w),     
        Vec3(center.x, center.y - h, center.z - w),     
        Vec3(center.x, center.y + h, center.z - w),     

        Vec3(center.x + w, center.y, center.z - h),     
        Vec3(center.x + w, center.y, center.z + h),     
        Vec3(center.x - w, center.y, center.z - h),     
        Vec3(center.x - w, center.y, center.z + h)      
    };

    int k = offset;
    tris[k + 0]  = Triangle(v[0], v[11], v[5],  color);
    tris[k + 1]  = Triangle(v[0], v[5],  v[1],  color);
    tris[k + 2]  = Triangle(v[0], v[1],  v[7],  color);
    tris[k + 3]  = Triangle(v[0], v[7],  v[10], color);
    tris[k + 4]  = Triangle(v[0], v[10], v[11], color);

    tris[k + 5]  = Triangle(v[1], v[5],  v[9],  color);
    tris[k + 6]  = Triangle(v[5], v[11], v[4],  color);
    tris[k + 7]  = Triangle(v[11], v[10], v[2], color);
    tris[k + 8]  = Triangle(v[10], v[7],  v[6], color);
    tris[k + 9]  = Triangle(v[7], v[1],   v[8], color);

    tris[k + 10] = Triangle(v[3], v[9],  v[4],  color);
    tris[k + 11] = Triangle(v[3], v[4],  v[2],  color);
    tris[k + 12] = Triangle(v[3], v[2],  v[6],  color);
    tris[k + 13] = Triangle(v[3], v[6],  v[8],  color);
    tris[k + 14] = Triangle(v[3], v[8],  v[9],  color);

    tris[k + 15] = Triangle(v[4], v[9],  v[5],  color);
    tris[k + 16] = Triangle(v[2], v[4],  v[11], color);
    tris[k + 17] = Triangle(v[6], v[2],  v[10], color);
    tris[k + 18] = Triangle(v[8], v[6],  v[7],  color);
    tris[k + 19] = Triangle(v[9], v[8],  v[1],  color);
}

void buildDodecahedron(const Vec3 &center,
                       double r,
                       uchar4 color,
                       Triangle *tris,
                       int offset) {
  double phi = (1.0 + sqrt(5.0)) / 2.0;
  double invPhi = 1.0 / phi;

  Vec3 v[20] = {
      Vec3(-invPhi, 0,       phi),
      Vec3( invPhi, 0,       phi),
      Vec3(-1,      1,       1),
      Vec3( 1,      1,       1),
      Vec3( 1,     -1,       1),
      Vec3(-1,     -1,       1),
      Vec3( 0,     -phi,     invPhi),
      Vec3( 0,      phi,     invPhi),
      Vec3(-phi,   -invPhi,  0),
      Vec3(-phi,    invPhi,  0),
      Vec3( phi,    invPhi,  0),
      Vec3( phi,   -invPhi,  0),
      Vec3( 0,     -phi,    -invPhi),
      Vec3( 0,      phi,    -invPhi),
      Vec3( 1,      1,      -1),
      Vec3( 1,     -1,      -1),
      Vec3(-1,     -1,      -1),
      Vec3(-1,      1,      -1),
      Vec3( invPhi, 0,      -phi),
      Vec3(-invPhi, 0,      -phi)
  };

  for (int i = 0; i < 20; ++i) {
    v[i].x = v[i].x * r / sqrt(3.0) + center.x;
    v[i].y = v[i].y * r / sqrt(3.0) + center.y;
    v[i].z = v[i].z * r / sqrt(3.0) + center.z;
  }

  int k = offset;
  tris[k++] = Triangle(v[4],  v[0],  v[6],  color);
  tris[k++] = Triangle(v[0],  v[5],  v[6],  color);
  tris[k++] = Triangle(v[0],  v[4],  v[1],  color);
  tris[k++] = Triangle(v[0],  v[3],  v[7],  color);
  tris[k++] = Triangle(v[2],  v[0],  v[7],  color);
  
  tris[k++] = Triangle(v[0],  v[1],  v[3],  color);
  tris[k++] = Triangle(v[10], v[1],  v[11], color);
  tris[k++] = Triangle(v[3],  v[1],  v[10], color);
  tris[k++] = Triangle(v[1],  v[4],  v[11], color);
  tris[k++] = Triangle(v[5],  v[0],  v[8],  color);
  
  tris[k++] = Triangle(v[0],  v[2],  v[9],  color);
  tris[k++] = Triangle(v[8],  v[0],  v[9],  color);
  tris[k++] = Triangle(v[5],  v[8],  v[16], color);
  tris[k++] = Triangle(v[6],  v[5],  v[12], color);
  tris[k++] = Triangle(v[12], v[5],  v[16], color);
  
  tris[k++] = Triangle(v[4],  v[12], v[15], color);
  tris[k++] = Triangle(v[4],  v[6],  v[12], color);
  tris[k++] = Triangle(v[11], v[4],  v[15], color);
  tris[k++] = Triangle(v[2],  v[13], v[17], color);
  tris[k++] = Triangle(v[2],  v[7],  v[13], color);
  
  tris[k++] = Triangle(v[9],  v[2],  v[17], color);
  tris[k++] = Triangle(v[13], v[3],  v[14], color);
  tris[k++] = Triangle(v[7],  v[3],  v[13], color);
  tris[k++] = Triangle(v[3],  v[10], v[14], color);
  tris[k++] = Triangle(v[8],  v[17], v[19], color);
  
  tris[k++] = Triangle(v[16], v[8],  v[19], color);
  tris[k++] = Triangle(v[8],  v[9],  v[17], color);
  tris[k++] = Triangle(v[14], v[11], v[18], color);
  tris[k++] = Triangle(v[11], v[15], v[18], color);
  tris[k++] = Triangle(v[10], v[11], v[14], color);
  
  tris[k++] = Triangle(v[12], v[19], v[18], color);
  tris[k++] = Triangle(v[15], v[12], v[18], color);
  tris[k++] = Triangle(v[12], v[16], v[19], color);
  tris[k++] = Triangle(v[19], v[13], v[18], color);
  tris[k++] = Triangle(v[17], v[13], v[19], color);
  tris[k++] = Triangle(v[13], v[14], v[18], color);
}

void values_for_report() {
  std::cout << "100\n";
  std::cout << "res/%d.data\n";
  std::cout << "600 600 120\n\n";

  std::cout << "10.0 3.0 0.0  4.0 1.0  2.0 6.0 1.0  0.0 0.0\n";
  std::cout << "2.0 0.0 0.0  0.5 0.1  1.0 4.0 1.0  0.0 0.0\n\n";

  // Цвета фигур 
  // Тетраэдр 
  std::cout << "3.0 3.0 0.5   0.9 0.5 0.6   2.0   0.0 0.0  0\n";
  // Икосаэдр 
  std::cout << "0.0 0.0 0.7   0.4 0.8 0.6   1.75  0.0 0.0  0\n";
  // Додекаэдр
  std::cout << "-3.0 -3.0 0.0 0.2 0.2 0.5   1.2   0.0 0.0  0\n\n";  
  
  // Цвет пола
  std::cout << "-40.0 -40.0 -1.0  -40.0 40.0 -1.0  40.0 40.0 -1.0  40.0 -40.0 -1.0 "
               "~/floor.data  0.15 0.15 0.15  0.0\n\n";
  std::cout << "1\n";
  std::cout << "-10.0 0.0 15.0  1.0 0.95 0.8\n\n";
  
  std::cout << "1 4\n";
}

struct AppConfig {
    int frames_number;
    char output_path[256];
    int w, h;
    double angle;

    double r0c, z0c, phi0c, Arc, Azc, wrc, wzc, wphic, prc, pzc;
    double r0n, z0n, phi0n, Arn, Azn, wrn, wzn, wphin, prn, pzn;

    Vec3 pos1, col1; double r1;
    Vec3 pos2, col2; double r2;
    Vec3 pos3, col3; double r3;

    Vec3 f[4];
    Vec3 floor_col;
    double floor_reflect;

    Vec3 light_pos;
    Vec3 light_col;

    int max_depth;
    int sr;
};


void readConfig(AppConfig &cfg) {
    std::cin >> cfg.frames_number;
    std::cin >> cfg.output_path;
    std::cin >> cfg.w >> cfg.h >> cfg.angle;

    std::cin >> cfg.r0c >> cfg.z0c >> cfg.phi0c >> cfg.Arc >> cfg.Azc >> cfg.wrc >> cfg.wzc >> cfg.wphic >> cfg.prc >> cfg.pzc;
    std::cin >> cfg.r0n >> cfg.z0n >> cfg.phi0n >> cfg.Arn >> cfg.Azn >> cfg.wrn >> cfg.wzn >> cfg.wphin >> cfg.prn >> cfg.pzn;

    double r, g, b, dump;
    
    std::cin >> cfg.pos1.x >> cfg.pos1.y >> cfg.pos1.z >> r >> g >> b >> cfg.r1 >> dump >> dump >> dump;
    cfg.col1 = Vec3(r, g, b);

    std::cin >> cfg.pos2.x >> cfg.pos2.y >> cfg.pos2.z >> r >> g >> b >> cfg.r2 >> dump >> dump >> dump;
    cfg.col2 = Vec3(r, g, b);

    std::cin >> cfg.pos3.x >> cfg.pos3.y >> cfg.pos3.z >> r >> g >> b >> cfg.r3 >> dump >> dump >> dump;
    cfg.col3 = Vec3(r, g, b);

    char tex_path[256];
    std::cin >> cfg.f[0].x >> cfg.f[0].y >> cfg.f[0].z
             >> cfg.f[1].x >> cfg.f[1].y >> cfg.f[1].z
             >> cfg.f[2].x >> cfg.f[2].y >> cfg.f[2].z
             >> cfg.f[3].x >> cfg.f[3].y >> cfg.f[3].z
             >> tex_path >> cfg.floor_col.x >> cfg.floor_col.y >> cfg.floor_col.z >> cfg.floor_reflect;

    int light_count;
    std::cin >> light_count;
    if (light_count > 0) {
        std::cin >> cfg.light_pos.x >> cfg.light_pos.y >> cfg.light_pos.z 
                 >> cfg.light_col.x >> cfg.light_col.y >> cfg.light_col.z;
        for (int i = 1; i < light_count; ++i) {
            double tx, ty, tz, tr, tg, tb;
            std::cin >> tx >> ty >> tz >> tr >> tg >> tb;
        }
    } else {
        cfg.light_pos = Vec3(-15.0, 0.0, 16.0); // Дефолтный свет
        cfg.light_col = Vec3(1.0, 1.0, 1.0);
    }

    std::cin >> cfg.max_depth >> r;
    cfg.sr = (int)r;
}

Camera computeCameraTrajectory(const AppConfig &cfg, int frame) {
    double t = 2.0 * M_PI * frame / cfg.frames_number;

    double rc   = cfg.r0c + cfg.Arc * std::cos(cfg.wrc * t + cfg.prc);
    double zc   = cfg.z0c + cfg.Azc * std::cos(cfg.wzc * t + cfg.pzc); 
    double phic = cfg.phi0c - cfg.wphic * t; 

    double rn   = cfg.r0n + cfg.Arn * std::cos(cfg.wrn * t + cfg.prn);
    double zn   = cfg.z0n + cfg.Azn * std::cos(cfg.wzn * t + cfg.pzn);
    double phin = cfg.phi0n - cfg.wphin * t;

    Camera cam;
    cam.pos    = Vec3(rc * std::cos(phic), rc * std::sin(phic), zc);
    cam.lookAt = Vec3(rn * std::cos(phin), rn * std::sin(phin), zn);
    cam.fovDeg = cfg.angle;
    return cam;
}

void saveFrame(const char* path_template, int frame, int w, int h, uchar4* data) {
    char filename[256];
    sprintf(filename, path_template, frame);
    FILE *f = fopen(filename, "wb");
    if (f) {
        fwrite(&w, sizeof(int), 1, f);
        fwrite(&h, sizeof(int), 1, f);
        fwrite(data, sizeof(uchar4), w * h, f);
        fclose(f);
    }
}

int main(int argc, char *argv[]) {
    if (argc >= 2 && strcmp(argv[1], "--default") == 0) {
        values_for_report();
        return 0;
    }

    AppConfig cfg;
    readConfig(cfg);

    Triangle tris[62];
    buildFloor(cfg.f[0], cfg.f[1], cfg.f[2], cfg.f[3], 
               make_uchar4(cfg.floor_col.x*255, cfg.floor_col.y*255, cfg.floor_col.z*255, 255), tris, 0);
    
    buildTetrahedron(Vec3(cfg.pos1.x + 2.0, cfg.pos1.y + 2.0, cfg.pos1.z + 0.8), cfg.r1 * 1.7,
                     make_uchar4(cfg.col1.x*255, cfg.col1.y*255, cfg.col1.z*255, 255), tris, 2);

    buildIcosahedron(Vec3(cfg.pos2.x, cfg.pos2.y - 3.0, cfg.pos2.z + 1.2), cfg.r2 * 1.5,
                     make_uchar4(cfg.col2.x*255, cfg.col2.y*255, cfg.col2.z*255, 255), tris, 6);

    buildDodecahedron(Vec3(cfg.pos3.x - 3.0, cfg.pos3.y - 3.0, cfg.pos3.z + 1.0), cfg.r3 * 1.6,
                      make_uchar4(cfg.col3.x*255, cfg.col3.y*255, cfg.col3.z*255, 255), tris, 26);

    uchar4 *imageCPU = (uchar4*)malloc(sizeof(uchar4) * cfg.w * cfg.h);
    uchar4 *imageGPU = NULL;
    Triangle *devTris = NULL;

    cudaMalloc(&imageGPU, sizeof(uchar4) * cfg.w * cfg.h);
    cudaMalloc(&devTris, sizeof(Triangle) * 62);
    cudaMemcpy(devTris, tris, sizeof(Triangle) * 62, cudaMemcpyHostToDevice);

    Scene devScene;
    devScene.tris = devTris;
    devScene.triCount = 62;
    devScene.lightPos = cfg.light_pos;
    devScene.lightColor = make_uchar4(cfg.light_col.x*255, cfg.light_col.y*255, cfg.light_col.z*255, 255);

    for (int frame = 0; frame < cfg.frames_number; ++frame) {
        Camera cam = computeCameraTrajectory(cfg, frame);
        
        float time_ms = 0.0f;
        cudaEvent_t start, stop;
        cudaEventCreate(&start);
        cudaEventCreate(&stop);
        cudaEventRecord(start);

        dim3 block(16, 16);
        dim3 grid(38, 38); 

        renderKernel<<<grid, block>>>(cam, cfg.w, cfg.h, cfg.sr, devScene, imageGPU);
        
        cudaMemcpy(imageCPU, imageGPU, sizeof(uchar4) * cfg.w * cfg.h, cudaMemcpyDeviceToHost);

        cudaEventRecord(stop);
        cudaEventSynchronize(stop);
        cudaEventElapsedTime(&time_ms, start, stop);
        
        saveFrame(cfg.output_path, frame, cfg.w, cfg.h, imageCPU);

        printf("%d\t%.4f\t%ld\n", frame + 1, time_ms, (long)cfg.w * cfg.h * cfg.sr * cfg.sr);

        cudaEventDestroy(start);
        cudaEventDestroy(stop);
    }

    cudaFree(imageGPU);
    cudaFree(devTris);
    free(imageCPU);

    return 0;
}