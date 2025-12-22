#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define CSC(call)                                               \
do {                                                            \
    cudaError_t status = call;                                  \
    if (status != cudaSuccess) {                                \
        fprintf(stderr, "ERROR in %s:%d. Message: %s\n",        \
                __FILE__, __LINE__, cudaGetErrorString(status));\
        exit(0);                                                \
    }                                                           \
} while (0)

#define MAX_CLASSES 32
#define DIM 3

typedef struct {
    int x, y;
} Point;

/* ---------- СРЕДНЕЕ ---------- */
void computeAVG(uchar4 *pixels, int width, int height,
                Point *points, int np, double avg[DIM]) {
    avg[0] = avg[1] = avg[2] = 0.0;

    for (int i = 0; i < np; ++i) {
        uchar4 p = pixels[points[i].x + points[i].y * width];
        avg[0] += p.x;
        avg[1] += p.y;
        avg[2] += p.z;
    }

    avg[0] /= np;
    avg[1] /= np;
    avg[2] /= np;
}

/* ---------- CONSTANT MEMORY ---------- */
struct ConstMem {
    double classMeanColors[MAX_CLASSES][DIM];
};
__constant__ ConstMem constMem;

/* ---------- МИНИМАЛЬНОЕ РАССТОЯНИЕ ---------- */
__device__ double distanceScore(uchar4 p, int classIdx) {
    double dx = p.x - constMem.classMeanColors[classIdx][0];
    double dy = p.y - constMem.classMeanColors[classIdx][1];
    double dz = p.z - constMem.classMeanColors[classIdx][2];

    return -(dx * dx + dy * dy + dz * dz);
}

__device__ int determinePixelClass(uchar4 p, int nc) {
    double bestScore = -1e18;
    int result = 0;

    for (int i = 0; i < nc; ++i) {
        double score = distanceScore(p, i);
        if (score > bestScore) {
            bestScore = score;
            result = i;
        }
    }
    return result;
}

/* ---------- KERNEL ---------- */
__global__ void kernel(uchar4 *pixels, int width, int height, int nc) {
    int idx = threadIdx.x + blockIdx.x * blockDim.x;
    int stride = blockDim.x * gridDim.x;
    int size = width * height;

    while (idx < size) {
        pixels[idx].w = determinePixelClass(pixels[idx], nc);
        idx += stride;
    }
}

/* ---------- MAIN ---------- */
int main() {
    char input_file[256], output_file[256];
    int nc;

    scanf("%s", input_file);
    scanf("%s", output_file);
    scanf("%d", &nc);

    Point **pixelPoints = (Point **)malloc(nc * sizeof(Point *));
    int *np = (int *)malloc(nc * sizeof(int));

    for (int i = 0; i < nc; ++i) {
        scanf("%d", &np[i]);
        pixelPoints[i] = (Point *)malloc(np[i] * sizeof(Point));
        for (int j = 0; j < np[i]; ++j)
            scanf("%d %d", &pixelPoints[i][j].x, &pixelPoints[i][j].y);
    }

    int width, height;
    FILE *infile = fopen(input_file, "rb");
    fread(&width, sizeof(int), 1, infile);
    fread(&height, sizeof(int), 1, infile);

    uchar4 *data = (uchar4 *)malloc(width * height * sizeof(uchar4));
    fread(data, sizeof(uchar4), width * height, infile);
    fclose(infile);

    double avgColors[MAX_CLASSES][DIM];
    for (int i = 0; i < nc; ++i)
        computeAVG(data, width, height, pixelPoints[i], np[i], avgColors[i]);

    ConstMem hostMem;
    memcpy(hostMem.classMeanColors, avgColors, sizeof(avgColors));
    CSC(cudaMemcpyToSymbol(constMem, &hostMem, sizeof(ConstMem)));

    uchar4 *dev_data;
    CSC(cudaMalloc(&dev_data, width * height * sizeof(uchar4)));
    CSC(cudaMemcpy(dev_data, data, width * height * sizeof(uchar4),
                   cudaMemcpyHostToDevice));

    kernel<<<1024, 1024>>>(dev_data, width, height, nc);
    CSC(cudaDeviceSynchronize());

    CSC(cudaMemcpy(data, dev_data, width * height * sizeof(uchar4),
                   cudaMemcpyDeviceToHost));

    FILE *outfile = fopen(output_file, "wb");
    fwrite(&width, sizeof(int), 1, outfile);
    fwrite(&height, sizeof(int), 1, outfile);
    fwrite(data, sizeof(uchar4), width * height, outfile);
    fclose(outfile);

    CSC(cudaFree(dev_data));
    free(data);
    for (int i = 0; i < nc; ++i) free(pixelPoints[i]);
    free(pixelPoints);
    free(np);

    return 0;
}
