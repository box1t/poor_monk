#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <array>
#include <cmath>
#include <chrono>

#include <cuda.h>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>

#define CSC(stmt)                                             \
do {                                                                 \
    cudaError_t err_ = (stmt);                                       \
    if (err_ != cudaSuccess) {                                       \
        fprintf(stderr, "CUDA error in %s:%d: %s\n",                 \
                __FILE__, __LINE__, cudaGetErrorString(err_));       \
        exit(EXIT_FAILURE);                                          \
    }                                                                \
} while(0)

struct Vector3 {
  double xComp, yComp, zComp;

  __host__ __device__
    Vector3(double x = 0, double y = 0, double z = 0) : xComp(x), yComp(y), zComp(z) {}

  __host__ __device__
    Vector3 plus(const Vector3& v) const {
    return Vector3(xComp + v.xComp, yComp + v.yComp, zComp + v.zComp);
  }

  __host__ __device__
    Vector3 minus(const Vector3& v) const {
    return Vector3(xComp - v.xComp, yComp - v.yComp, zComp - v.zComp);
  }

  __host__ __device__
    Vector3 times(double s) const {
    return Vector3(xComp * s, yComp * s, zComp * s);
  }

  __host__ __device__
    Vector3 divide(double s) const {
    return Vector3(xComp / s, yComp / s, zComp / s);
  }

  __host__ __device__
    double dotProd(const Vector3& v) const {
    return xComp * v.xComp + yComp * v.yComp + zComp * v.zComp;
  }

  __host__ __device__
    Vector3 crossProd(const Vector3& v) const {
    return Vector3(
      yComp * v.zComp - zComp * v.yComp,
      zComp * v.xComp - xComp * v.zComp,
      xComp * v.yComp - yComp * v.xComp
    );
  }

  __host__ __device__
    double lengthVal() const {
    return sqrt(xComp * xComp + yComp * yComp + zComp * zComp);
  }

  __host__ __device__
    Vector3 normalized() const {
    double len_ = lengthVal();
    return (len_ < 1e-12) ? *this : Vector3(xComp / len_, yComp / len_, zComp / len_);
  }

  __host__ __device__
    Vector3 transformBy(const Vector3& basis1, const Vector3& basis2, const Vector3& basis3) const {
    return Vector3(
      basis1.xComp * xComp + basis2.xComp * yComp + basis3.xComp * zComp,
      basis1.yComp * xComp + basis2.yComp * yComp + basis3.yComp * zComp,
      basis1.zComp * xComp + basis2.zComp * yComp + basis3.zComp * zComp
    );
  }
};

struct ColorRGBA {
  double rChan, gChan, bChan, aChan;
};

struct MeshInfo {
    Vector3 center;
    double radius;
    size_t startIdx;
    size_t count;
};

__host__ __device__
bool intersectSphere(const Vector3& orig, const Vector3& dir, const Vector3& center, double radius) {
    Vector3 oc = orig.minus(center);
    double b = oc.dotProd(dir);
    double c = oc.dotProd(oc) - radius * radius;
    if (c > 0.0f && b > 0.0f) return false;
    double discr = b * b - c;
    if (discr < 0.0f) return false;
    return true;
}

struct TriPrim {
  Vector3 p0, p1, p2;
  Vector3 n0, n1, n2; 

  __host__ __device__
    Vector3 getInterpolatedNormal(double u, double v) const {
        double w = 1.0 - u - v;
        return n0.times(w).plus(n1.times(u)).plus(n2.times(v)).normalized();
    }

    __host__ __device__
    Vector3 getFlatNormal() const {
        return (p1.minus(p0)).crossProd(p2.minus(p0)).normalized();
    }

  __host__ __device__
    Vector3 getNormal() const {
    Vector3 n_ = (p1.minus(p0)).crossProd(p2.minus(p0));
    return n_.normalized();
  }
};

struct Illumination {
  Vector3 pos;
  ColorRGBA tint;
};

struct HitRecord {
  bool    isHit;
  size_t  shapeIndex;
  double  tDist;
};

struct SegmentGlow {
  int     segments;
  Vector3 glowStart, glowEnd;
};

struct SceneObject {
  TriPrim    tri;
  ColorRGBA  surfColor;
  SegmentGlow glowData;

  __host__ __device__
    SceneObject() {
    glowData.segments = 0;
    glowData.glowStart = Vector3(0, 0, 0);
    glowData.glowEnd = Vector3(0, 0, 0);
  }
};

__host__ __device__
bool checkAxisAlignment(const Vector3& vA, const Vector3& vB) {
  Vector3 diff_ = vB.minus(vA);
  int countNonZero = 0;
  if (fabs(diff_.xComp) > 1e-6) countNonZero++;
  if (fabs(diff_.yComp) > 1e-6) countNonZero++;
  if (fabs(diff_.zComp) > 1e-6) countNonZero++;
  return (countNonZero == 1);
}

static std::vector<TriPrim> createTetrahedron() {
    double a = 1.0;
    Vector3 p0(a, a, a);
    Vector3 p1(-a, -a, a);
    Vector3 p2(-a, a, -a);
    Vector3 p3(a, -a, -a);

    return {
        {p0, p1, p2}, {p0, p3, p1},
        {p0, p2, p3}, {p1, p3, p2}
    };
}

struct MeshGroup {
  Vector3 center;
  double radiusSq;
  int startIdx;
  int count;
};

static std::vector<TriPrim> createIcosahedron() {
    double phi = (1.0 + sqrt(5.0)) / 2.0; // Золотое сечение
    std::vector<Vector3> v = {
        {-1,  phi, 0}, { 1,  phi, 0}, {-1, -phi, 0}, { 1, -phi, 0},
        { 0, -1,  phi}, { 0,  1,  phi}, { 0, -1, -phi}, { 0,  1, -phi},
        { phi, 0, -1}, { phi, 0,  1}, {-phi, 0, -1}, {-phi, 0,  1}
    };

    return {
        {v[0], v[11], v[5]}, {v[0], v[5], v[1]}, {v[0], v[1], v[7]}, {v[0], v[7], v[10]}, {v[0], v[10], v[11]},
        {v[1], v[5], v[9]}, {v[5], v[11], v[4]}, {v[11], v[10], v[2]}, {v[10], v[7], v[6]}, {v[7], v[1], v[8]},
        {v[3], v[9], v[4]}, {v[3], v[4], v[2]}, {v[3], v[2], v[6]}, {v[3], v[6], v[8]}, {v[3], v[8], v[9]},
        {v[4], v[9], v[5]}, {v[2], v[4], v[11]}, {v[6], v[2], v[10]}, {v[8], v[6], v[7]}, {v[9], v[8], v[1]}
    };
}

static std::vector<TriPrim> createDodecahedron() {
    double phi = (1.0 + sqrt(5.0)) / 2.0;
    double invPhi = 1.0 / phi;
    
    std::vector<Vector3> v = {
        {1, 1, 1}, {1, 1, -1}, {1, -1, 1}, {1, -1, -1},
        {-1, 1, 1}, {-1, 1, -1}, {-1, -1, 1}, {-1, -1, -1},
        {0, invPhi, phi}, {0, invPhi, -phi}, {0, -invPhi, phi}, {0, -invPhi, -phi},
        {invPhi, phi, 0}, {invPhi, -phi, 0}, {-invPhi, phi, 0}, {-invPhi, -phi, 0},
        {phi, 0, invPhi}, {phi, 0, -invPhi}, {-phi, 0, invPhi}, {-phi, 0, -invPhi}
    };

    auto addPentagon = [&](int a, int b, int c, int d, int e, std::vector<TriPrim>& faces) {
        faces.push_back({v[a], v[b], v[c]});
        faces.push_back({v[a], v[c], v[d]});
        faces.push_back({v[a], v[d], v[e]});
    };

    std::vector<TriPrim> faces;
    addPentagon(0, 8, 10, 2, 16, faces);   addPentagon(0, 16, 17, 1, 12, faces);
    addPentagon(0, 12, 14, 4, 8, faces);   addPentagon(8, 4, 18, 6, 10, faces);
    addPentagon(10, 6, 15, 3, 2, faces);   addPentagon(16, 2, 3, 13, 17, faces);
    addPentagon(1, 17, 13, 11, 9, faces);  addPentagon(1, 9, 5, 14, 12, faces);
    addPentagon(4, 14, 5, 19, 18, faces);  addPentagon(18, 19, 7, 15, 6, faces);
    addPentagon(15, 7, 11, 13, 3, faces);  addPentagon(7, 19, 5, 9, 11, faces);
    return faces;
}

void transformPrims(std::vector<TriPrim>& arr, const Vector3& offset, double scaleVal) {
    for (auto& tp : arr) {
        tp.p0 = tp.p0.times(scaleVal).plus(offset);
        tp.p1 = tp.p1.times(scaleVal).plus(offset);
        tp.p2 = tp.p2.times(scaleVal).plus(offset);
    }
}

template<size_t N>
void shiftAndScalePrimitives(std::array<TriPrim, N>& arr, const Vector3& offset, double scaleVal) {
  for (auto& tp : arr) {
    tp.p0 = tp.p0.times(scaleVal).plus(offset);
    tp.p1 = tp.p1.times(scaleVal).plus(offset);
    tp.p2 = tp.p2.times(scaleVal).plus(offset);
  }
}

__host__ __device__
bool intersectBoundingSphere(const Vector3& orig, const Vector3& dir, const Vector3& center, double radSq) {
    Vector3 l = center.minus(orig);
    double tca = l.dotProd(dir);
    if (tca < 0) return false;
    double d2 = l.dotProd(l) - tca * tca;
    return d2 <= radSq;
}

__host__ __device__
HitRecord checkHits(const Vector3& orig, const Vector3& dir,
  double minT, double maxT,
  const SceneObject* shapes, const MeshGroup* groups, int groupCount)
{
  HitRecord hres;
  hres.isHit = false;
  hres.tDist = maxT;

  for (int g = 0; g < groupCount; ++g) {
    // Если луч не пересекает сферу — пропускаем все треугольники меша
    if (!intersectBoundingSphere(orig, dir, groups[g].center, groups[g].radiusSq)) {
      continue;
    }

    for (int i = groups[g].startIdx; i < groups[g].startIdx + groups[g].count; ++i) {
      const TriPrim& tri = shapes[i].tri;
      Vector3 e1 = tri.p1.minus(tri.p0);
      Vector3 e2 = tri.p2.minus(tri.p0);
      Vector3 pV = dir.crossProd(e2);
      double d_ = e1.dotProd(pV);
      
      if (fabs(d_) < 1e-14) continue;
      
      Vector3 tV = orig.minus(tri.p0);
      double u_ = tV.dotProd(pV) / d_;
      if (u_ < 0.0 || u_ > 1.0) continue;
      
      Vector3 qV = tV.crossProd(e1);
      double v_ = dir.dotProd(qV) / d_;
      if (v_ < 0.0 || (u_ + v_) > 1.0) continue;
      
      double t_ = e2.dotProd(qV) / d_;
      if (t_ > minT && t_ < hres.tDist) {
        hres.isHit = true;
        hres.tDist = t_;
        hres.shapeIndex = i;
        // Сохраняем барицентрические координаты для нормали (опционально в HitRecord)
      }
    }
  }
  return hres;
}

__host__ __device__
ColorRGBA getShadingColor(const SceneObject& obj, const Illumination& lamp,
  const Vector3& hitPnt, const Vector3& viewRay,
  const SceneObject* shapes, size_t shapeCount)
{
  ColorRGBA cOut;
  double ambientVal = 0.25;

  Vector3 toLight = lamp.pos.minus(hitPnt);
  double dist2light = toLight.lengthVal();
  if (dist2light < 1e-12) dist2light = 1e-12;
  Vector3 LDir = toLight.normalized();

  double visFactor = 1.0;
  Vector3 checkPt = hitPnt.plus(LDir.times(1e-5));
  double remain_ = dist2light - 1e-5;
  while (true) {
    if (visFactor < 1e-6) {
      visFactor = 0.0;
      break;
    }
    HitRecord hrx = checkHits(checkPt, LDir, 0.0, remain_, shapes, shapeCount);
    if (!hrx.isHit) break;
    double tH = hrx.tDist;
    if (tH < 1e-5) break;
    double alphaVal = shapes[hrx.shapeIndex].surfColor.aChan;
    double passFrac = 1.0 - alphaVal;
    if (passFrac < 0) passFrac = 0.0;
    visFactor *= passFrac;
    if (visFactor < 1e-6) {
      visFactor = 0.0;
      break;
    }
    checkPt = checkPt.plus(LDir.times(tH)).plus(LDir.times(1e-5));
    remain_ -= tH;
    if (remain_ < 1e-5) break;
  }

  if (visFactor < 1e-6) {
    double intensity = ambientVal;
    cOut.rChan = obj.surfColor.rChan * lamp.tint.rChan * intensity;
    cOut.gChan = obj.surfColor.gChan * lamp.tint.gChan * intensity;
    cOut.bChan = obj.surfColor.bChan * lamp.tint.bChan * intensity;
    cOut.aChan = obj.surfColor.aChan;
    return cOut;
  }

  Vector3 norm_ = obj.tri.getInterpolatedNormal(baryB_, baryC_);
  double dotNL = norm_.dotProd(LDir);
  if (dotNL < 0) dotNL = 0;
  Vector3 reflectionRay = norm_.times(2.0 * dotNL).minus(LDir);
  double spec_ = reflectionRay.dotProd(viewRay);
  if (spec_ < 0) spec_ = 0;
  spec_ = pow(spec_, 32.0) * 0.5;
  double diffuse_ = 1.0 * dotNL;
  double finalInt = ambientVal + (diffuse_ + spec_) * visFactor;
  cOut.rChan = obj.surfColor.rChan * lamp.tint.rChan * finalInt;
  cOut.gChan = obj.surfColor.gChan * lamp.tint.gChan * finalInt;
  cOut.bChan = obj.surfColor.bChan * lamp.tint.bChan * finalInt;
  cOut.aChan = obj.surfColor.aChan;

  bool boxTest = false;
  if (fabs(obj.surfColor.rChan) < 0.01 &&
    fabs(obj.surfColor.gChan) < 0.01 &&
    fabs(obj.surfColor.bChan - 1.0) < 0.01)
  {
    boxTest = true;
  }

  if (!(fabs(obj.surfColor.rChan - 0.3) < 0.01 &&
    fabs(obj.surfColor.gChan - 0.3) < 0.01 &&
    fabs(obj.surfColor.bChan - 0.3) < 0.01))
  {
    const Vector3& A_ = obj.tri.p0;
    const Vector3& B_ = obj.tri.p1;
    const Vector3& C_ = obj.tri.p2;
    Vector3 v0_ = B_.minus(A_);
    Vector3 v1_ = C_.minus(A_);
    Vector3 v2_ = hitPnt.minus(A_);
    double d00_ = v0_.dotProd(v0_);
    double d01_ = v0_.dotProd(v1_);
    double d11_ = v1_.dotProd(v1_);
    double d20_ = v2_.dotProd(v0_);
    double d21_ = v2_.dotProd(v1_);
    double denom_ = d00_ * d11_ - d01_ * d01_;
    double baryA_ = 1.0 - ((d11_ * d20_ - d01_ * d21_) / denom_)
      - ((d00_ * d21_ - d01_ * d20_) / denom_);
    double baryB_ = (d11_ * d20_ - d01_ * d21_) / denom_;
    double baryC_ = (d00_ * d21_ - d01_ * d20_) / denom_;
    Vector3 norm_;
    if (obj.glowData.segments == -1) { // Маркер для плоских объектов (пол)
        norm_ = obj.tri.getFlatNormal();
    } else {
        norm_ = obj.tri.getSmoothNormal(baryB_, baryC_);
    }
    
    if (fabs(baryA_) < 0.05) {
      if (!boxTest || checkAxisAlignment(B_, C_)) {
        cOut.rChan = cOut.gChan = cOut.bChan = 0;
      }
    }
    else if (fabs(baryB_) < 0.05) {
      if (!boxTest || checkAxisAlignment(A_, C_)) {
        cOut.rChan = cOut.gChan = cOut.bChan = 0;
      }
    }
    else if (fabs(baryC_) < 0.05) {
      if (!boxTest || checkAxisAlignment(A_, B_)) {
        cOut.rChan = cOut.gChan = cOut.bChan = 0;
      }
    }
  }

  int segCount = obj.glowData.segments;
  if (segCount > 0) {
    bool wasHighlighted = false;
    Vector3 triPoints[3] = { obj.tri.p0, obj.tri.p1, obj.tri.p2 };
    for (int jj = 0; jj < 3 && !wasHighlighted; jj++) {
      Vector3 A_ = triPoints[jj];
      Vector3 B_ = triPoints[(jj + 1) % 3];
      if (boxTest && !checkAxisAlignment(A_, B_)) {
        continue;
      }
      for (int ii = 1; ii <= segCount; ii++) {
        double alpha_ = double(ii) / (segCount + 1);
        Vector3 edgePt_ = A_.times(1.0 - alpha_).plus(B_.times(alpha_));
        if (hitPnt.minus(edgePt_).lengthVal() < 0.05) {
          cOut.rChan *= 2.0;
          cOut.gChan *= 2.0;
          cOut.bChan *= 2.0;
          wasHighlighted = true;
          break;
        }
      }
    }
  }

  return cOut;
}

__host__ __device__
ColorRGBA rayTrace(const Vector3& origin, const Vector3& dir_,
  double tLow, double tHigh,
  const SceneObject* shapes, size_t shapeCount,
  const Illumination& lamp, int depth);

__host__ __device__
ColorRGBA getReflectionColor(const Vector3& o_, const Vector3& d_,
  double tLow, double tHigh,
  const SceneObject* shapes, size_t shapeCount,
  const Illumination& lamp, int depth)
{
  return rayTrace(o_, d_, tLow, tHigh, shapes, shapeCount, lamp, depth - 1);
}

__host__ __device__
ColorRGBA rayTrace(const Vector3& origin, const Vector3& dir_,
  double tLow, double tHigh,
  const SceneObject* shapes, size_t shapeCount,
  const Illumination& lamp, int depth)
{
  if (depth <= 0) {
    return { 0, 0, 0, 1 };
  }

  HitRecord hRec = checkHits(origin, dir_, tLow, tHigh, shapes, shapeCount);
  if (!hRec.isHit) {
    return { 0, 0, 0, 1 };
  }

  double tHit_ = hRec.tDist;
  Vector3 impactPos = origin.plus(dir_.times(tHit_));
  const SceneObject& curS = shapes[hRec.shapeIndex];

  Vector3 normedDir = dir_.normalized();
  Vector3 vantage = normedDir.times(-1.0);

  ColorRGBA localC = getShadingColor(curS, lamp, impactPos, vantage, shapes, shapeCount);

  Vector3 normalFace = curS.tri.getNormal();
  double costh_ = fabs(normedDir.dotProd(normalFace));
  double fres_ = 0.04 + (1.0 - 0.04) * pow(1.0 - costh_, 5);
  double reflW = 2.0 * fres_;

  Vector3 rDir = normedDir.minus(normalFace.times(2.0 * (normedDir.dotProd(normalFace))));
  Vector3 rOri = impactPos.plus(rDir.times(1e-5));
  ColorRGBA reflectC = rayTrace(rOri, rDir, tLow, tHigh, shapes, shapeCount, lamp, depth - 1);

  if (curS.surfColor.aChan >= 1.0) {
    ColorRGBA finalOut;
    finalOut.rChan = localC.rChan * (1 - reflW) + reflectC.rChan * reflW;
    finalOut.gChan = localC.gChan * (1 - reflW) + reflectC.gChan * reflW;
    finalOut.bChan = localC.bChan * (1 - reflW) + reflectC.bChan * reflW;
    finalOut.aChan = 1.0;
    return finalOut;
  }
  else {
    Vector3 tOri = impactPos.plus(normedDir.times(1e-5));
    ColorRGBA behind = rayTrace(tOri, dir_, tLow, tHigh, shapes, shapeCount, lamp, depth - 1);
    double alphaPart = curS.surfColor.aChan;
    ColorRGBA blended;
    blended.rChan = localC.rChan * alphaPart + behind.rChan * (1 - alphaPart);
    blended.gChan = localC.gChan * alphaPart + behind.gChan * (1 - alphaPart);
    blended.bChan = localC.bChan * alphaPart + behind.bChan * (1 - alphaPart);
    blended.aChan = 1.0;

    ColorRGBA outF;
    outF.rChan = blended.rChan * (1 - reflW) + reflectC.rChan * reflW;
    outF.gChan = blended.gChan * (1 - reflW) + reflectC.gChan * reflW;
    outF.bChan = blended.bChan * (1 - reflW) + reflectC.bChan * reflW;
    outF.aChan = 1.0;
    return outF;
  }
}

struct FramePixel {
  unsigned char r, g, b, a;
};

static dim3 deviceBlock;
static dim3 deviceGrid;

__global__ void deviceRenderKernel(FramePixel* outFB, int w_, int h_, const SceneObject* shapes, 
    int shapeCount, Illumination lamp, double fovVal, Vector3 camLoc, Vector3 lookAt)
{
  double aspect = double(h_) / double(w_);
  double dx_ = 2.0 / (w_ - 1.0);
  double dy_ = 2.0 / (h_ - 1.0);
  double distPlane = 1.0 / tan(fovVal / 2.0);

  Vector3 fwd = lookAt.minus(camLoc).normalized();
  Vector3 upv(0, 0, 1);
  Vector3 rght = fwd.crossProd(upv).normalized();
  Vector3 trueUp = rght.crossProd(fwd).normalized();

  double bigVal = 1e20;
  int ix_ = blockIdx.x * blockDim.x + threadIdx.x;
  int iy_ = blockIdx.y * blockDim.y + threadIdx.y;

  if (ix_ < w_ && iy_ < h_) {
    Vector3 rDir(-1.0 + ix_ * dx_, -1.0 + iy_ * dy_, distPlane);
    rDir.yComp *= aspect;
    rDir = rDir.transformBy(rght, trueUp, fwd);

    ColorRGBA col_ = rayTrace(camLoc, rDir, 1e-5, bigVal,
      shapes, shapeCount, lamp, 5);

    double rr = col_.rChan, gg = col_.gChan, bb = col_.bChan;
    if (rr > 1) rr = 1; if (rr < 0) rr = 0;
    if (gg > 1) gg = 1; if (gg < 0) gg = 0;
    if (bb > 1) bb = 1; if (bb < 0) bb = 0;

    int idx_ = (h_ - 1 - iy_) * w_ + ix_;
    outFB[idx_].r = (unsigned char)(rr * 255);
    outFB[idx_].g = (unsigned char)(gg * 255);
    outFB[idx_].b = (unsigned char)(bb * 255);
    outFB[idx_].a = 255;
  }
}


void hostRender(FramePixel* fbPtr, int w_, int h_,
  const SceneObject* shapes, int shapeCount,
  Illumination lamp, double fovVal,
  Vector3 camLoc, Vector3 lookAt)
{
  double aspect = double(h_) / double(w_);
  double dx_ = 2.0 / (w_ - 1.0);
  double dy_ = 2.0 / (h_ - 1.0);
  double distPlane = 1.0 / tan(fovVal / 2.0);

  Vector3 fwd = lookAt.minus(camLoc).normalized();
  Vector3 upv(0, 0, 1);
  Vector3 rght = fwd.crossProd(upv).normalized();
  Vector3 trueUp = rght.crossProd(fwd).normalized();

  double bigVal = 1e20;
  for (int jj = 0; jj < h_; jj++) {
    for (int ii = 0; ii < w_; ii++) {
      Vector3 rDir(-1.0 + ii * dx_, -1.0 + jj * dy_, distPlane);
      rDir.yComp *= aspect;
      rDir = rDir.transformBy(rght, trueUp, fwd);

      ColorRGBA cRes = rayTrace(camLoc, rDir, 1e-5, bigVal,
        shapes, shapeCount, lamp, 5);
      double rr = cRes.rChan, gg = cRes.gChan, bb = cRes.bChan;
      if (rr > 1) rr = 1; if (rr < 0) rr = 0;
      if (gg > 1) gg = 1; if (gg < 0) gg = 0;
      if (bb > 1) bb = 1; if (bb < 0) bb = 0;

      int idx_ = (h_ - 1 - jj) * w_ + ii;
      fbPtr[idx_].r = (unsigned char)(rr * 255);
      fbPtr[idx_].g = (unsigned char)(gg * 255);
      fbPtr[idx_].b = (unsigned char)(bb * 255);
      fbPtr[idx_].a = 255;
    }
  }
}

struct ProgramInput {
  bool    runOnDevice;
  int     totalFrames;
  int     imgWidth;
  int     imgHeight;
  double  camFovDeg;
  double  revolveRad;
  Vector3 camPos;
  Vector3 lookAt;
  Illumination mainLight;

  Vector3 posA, posB, posC;
  double  scaleA, scaleB, scaleC;
};

bool parseCmdFlags(int argc, char** argv)
{
  if (argc < 2) {
    return true;
  }
  else {
    std::string opt_(argv[1]);
    if (opt_ == "--default") {
      std::cout << "300 1024 768 60 4.0\n"
        << "0 -3 1\n"
        << "0 0 0\n"
        << "3 -3 5\n"
        << "1 1 1\n"
        << "-2 0 0 1.0\n"
        << "0 0 0 1.0\n"
        << "2 0 0 1.0\n";
      exit(0);
    }
    else if (opt_ == "--gpu") {
      return true;
    }
    else if (opt_ == "--cpu") {
      return false;
    }
    else {
      std::cerr << "Unknown option: " << opt_ << "\n";
      exit(-1);
    }
  }
  return true;
}

ProgramInput retrieveSceneInput(bool runOnGPU)
{
  ProgramInput st;
  st.runOnDevice = runOnGPU;

  std::cin >> st.totalFrames >> st.imgWidth >> st.imgHeight
    >> st.camFovDeg >> st.revolveRad;
  if (!std::cin.good()) {
    throw std::runtime_error("Expected: frames width height fov_deg revolve_radius");
  }

  std::cin >> st.camPos.xComp >> st.camPos.yComp >> st.camPos.zComp;
  std::cin >> st.lookAt.xComp >> st.lookAt.yComp >> st.lookAt.zComp;

  std::cin >> st.mainLight.pos.xComp
    >> st.mainLight.pos.yComp
    >> st.mainLight.pos.zComp;

  std::cin >> st.mainLight.tint.rChan
    >> st.mainLight.tint.gChan
    >> st.mainLight.tint.bChan;

  std::cin >> st.posA.xComp >> st.posA.yComp >> st.posA.zComp >> st.scaleA;
  std::cin >> st.posB.xComp >> st.posB.yComp >> st.posB.zComp >> st.scaleB;
  std::cin >> st.posC.xComp >> st.posC.yComp >> st.posC.zComp >> st.scaleC;

  return st;
}

std::vector<SceneObject> assembleScene(const ProgramInput& inputData)
{
    auto tetraPrims = createTetrahedron();
    auto icoPrims = createIcosahedron();
    auto dodecaPrims = createDodecahedron();

    // Масштабируем и перемещаем
    transformPrims(tetraPrims, inputData.posA, inputData.scaleA);
    transformPrims(icoPrims, inputData.posB, inputData.scaleB * 0.5); // Икосаэдр чуть крупнее по координатам
    transformPrims(dodecaPrims, inputData.posC, inputData.scaleC * 0.5);

    std::vector<SceneObject> results;

    // 1. Тетраэдр (Красный)
    for (auto& tp : tetraPrims) {
        SceneObject so;
        so.tri = tp;
        so.surfColor = { 1.0, 0.2, 0.2, 0.7 }; // Красный полупрозрачный
        so.glowData.segments = 2;
        results.push_back(so);
    }

    // 2. Икосаэдр (Синий)
    for (auto& tp : icoPrims) {
        SceneObject so;
        so.tri = tp;
        so.surfColor = { 0.4, 0.6, 1.0, 0.3 }; // Синий
        so.glowData.segments = 0; // Слишком много граней для свечения
        results.push_back(so);
    }

    // 3. Додекаэдр (Зеленый)
    for (auto& tp : dodecaPrims) {
        SceneObject so;
        so.tri = tp;
        so.surfColor = { 0.2, 1.0, 0.2, 0.6 }; // Зеленый
        so.glowData.segments = 0;
        results.push_back(so);
    }

    // Пол (как в оригинале)
    {
        Vector3 pA(-15, -15, -5), pB(15, -15, -5), pC(15, 15, -5), pD(-15, 15, -5);
        SceneObject f1, f2;
        f1.tri = {pA, pB, pC}; f1.surfColor = {0.3, 0.3, 0.3, 1.0};
        f2.tri = {pA, pC, pD}; f2.surfColor = {0.3, 0.3, 0.3, 1.0};
        results.push_back(f1);
        results.push_back(f2);
    }

    return results;
}

void hostRenderSequence(const ProgramInput& pp,
  const std::vector<SceneObject>& worldShapes)
{
  std::vector<FramePixel> tempFB(pp.imgWidth * pp.imgHeight);
  size_t shapeCount = worldShapes.size();
  double fovRads = pp.camFovDeg * M_PI / 180.0;

  for (int fID = 0; fID < pp.totalFrames; fID++) {
    double ang = 4.0 * M_PI * double(fID) / pp.totalFrames;
    Vector3 currCam = pp.camPos;
    if (pp.revolveRad > 1e-9) {
      currCam.xComp = pp.lookAt.xComp + pp.revolveRad * cos(ang);
      currCam.yComp = pp.lookAt.yComp + pp.revolveRad * sin(ang);
    }
    auto tStart = std::chrono::high_resolution_clock::now();
    hostRender(tempFB.data(), pp.imgWidth, pp.imgHeight,
      worldShapes.data(), int(shapeCount),
      pp.mainLight, fovRads,
      currCam, pp.lookAt);
    auto tEnd = std::chrono::high_resolution_clock::now();
    double ms_ = std::chrono::duration<double, std::milli>(tEnd - tStart).count();
    std::cout << "frame " << fID << " of " << pp.totalFrames
      << " time=" << ms_ << " ms\n";

    char fname[32];
    sprintf(fname, "frame_%03d.data", fID);
    std::ofstream ofs(fname, std::ios::binary);
    int w = pp.imgWidth, h = pp.imgHeight;
    ofs.write((char*)&w, sizeof(int));
    ofs.write((char*)&h, sizeof(int));
    ofs.write((char*)tempFB.data(), w * h * sizeof(FramePixel));
  }
}

void deviceRenderSequence(const ProgramInput& pp,
  const std::vector<SceneObject>& worldShapes)
{
  CSC(cudaDeviceSetLimit(cudaLimitStackSize, 32768));

  int blkX = 16, blkY = 16;
  int grdX = (pp.imgWidth + blkX - 1) / blkX;
  int grdY = (pp.imgHeight + blkY - 1) / blkY;
  deviceBlock = dim3(blkX, blkY);
  deviceGrid = dim3(grdX, grdY);

  SceneObject* gpuShapes = nullptr;
  size_t shapeCount = worldShapes.size();

  CSC(cudaMalloc(&gpuShapes, shapeCount * sizeof(SceneObject)));
  CSC(cudaMemcpy(gpuShapes, worldShapes.data(),
    shapeCount * sizeof(SceneObject),
    cudaMemcpyHostToDevice));

  FramePixel* gpuFrame = nullptr;
  CSC(cudaMalloc(&gpuFrame, pp.imgWidth * pp.imgHeight * sizeof(FramePixel)));

  std::vector<FramePixel> localFB(pp.imgWidth * pp.imgHeight);
  double fovRads = pp.camFovDeg * M_PI / 180.0;

  cudaEvent_t startEvt, stopEvt;
  CSC(cudaEventCreate(&startEvt));
  CSC(cudaEventCreate(&stopEvt));

  for (int fID = 0; fID < pp.totalFrames; fID++) {
    double ang = 4.0 * M_PI * double(fID) / pp.totalFrames;
    Vector3 currCam = pp.camPos;
    if (pp.revolveRad > 1e-9) {
      currCam.xComp = pp.lookAt.xComp + pp.revolveRad * cos(ang);
      currCam.yComp = pp.lookAt.yComp + pp.revolveRad * sin(ang);
    }

    CSC(cudaEventRecord(startEvt));
    deviceRenderKernel << <deviceGrid, deviceBlock >> > (
      gpuFrame, pp.imgWidth, pp.imgHeight,
      gpuShapes, int(shapeCount),
      pp.mainLight, fovRads,
      currCam, pp.lookAt
      );
    CSC(cudaGetLastError());
    CSC(cudaDeviceSynchronize());
    CSC(cudaEventRecord(stopEvt));
    CSC(cudaEventSynchronize(stopEvt));

    float msElapsed = 0;
    CSC(cudaEventElapsedTime(&msElapsed, startEvt, stopEvt));

    CSC(cudaMemcpy(localFB.data(), gpuFrame,
      pp.imgWidth * pp.imgHeight * sizeof(FramePixel),
      cudaMemcpyDeviceToHost));

    std::cout << "frame " << fID << " of " << pp.totalFrames
      << " time=" << msElapsed << " ms\n";

    char fname[32];
    sprintf(fname, "frame_%03d.data", fID);
    std::ofstream ofs(fname, std::ios::binary);
    int w = pp.imgWidth, h = pp.imgHeight;
    ofs.write((char*)&w, sizeof(int));
    ofs.write((char*)&h, sizeof(int));
    ofs.write((char*)localFB.data(), w * h * sizeof(FramePixel));
  }

  CSC(cudaFree(gpuShapes));
  CSC(cudaFree(gpuFrame));
  CSC(cudaEventDestroy(startEvt));
  CSC(cudaEventDestroy(stopEvt));
}

int main(int argc, char** argv)
{
  bool runOnDev = parseCmdFlags(argc, argv);

  ProgramInput pData = retrieveSceneInput(runOnDev);

  std::vector<SceneObject> worldSet = assembleScene(pData);

  if (pData.runOnDevice) {
    deviceRenderSequence(pData, worldSet);
  }
  else {
    hostRenderSequence(pData, worldSet);
  }

  return 0;
}