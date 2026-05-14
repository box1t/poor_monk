#include <stdio.h>
#include <stdlib.h>
#include <string.h> // для memset

#define CSC(call)                                   \
do {                                          \
  cudaError_t res = call;                             \
  if (res != cudaSuccess) {                         \
    fprintf(stderr, "ERROR in %s:%d. Message: %s\n",      \
        __FILE__, __LINE__, cudaGetErrorString(res));   \
    exit(0);                                    \
  }                                           \
} while(0)

__device__ float get_gray(uchar4 p) {
    return 0.299f * p.x + 0.587f * p.y + 0.114f * p.z;
}

__global__ void kernel(cudaTextureObject_t tex, uchar4 *out, int w, int h) {
    int idx = blockDim.x * blockIdx.x + threadIdx.x;
    int idy = blockDim.y * blockIdx.y + threadIdx.y;
    int offsetx = blockDim.x * gridDim.x;
    int offsety = blockDim.y * gridDim.y;

    float dx = 1.0f / w;
    float dy = 1.0f / h;

    for (int y = idy; y < h; y += offsety) {
        for (int x = idx; x < w; x += offsetx) {
            float fx = (x + 0.5f) / w;
            float fy = (y + 0.5f) / h;

            // вычисление интенсивности пикселей в 3x3
            // чтение текстуры с нормализованными координатами
            float p00 = get_gray(tex2D<uchar4>(tex, fx - dx, fy - dy));
            float p01 = get_gray(tex2D<uchar4>(tex, fx,      fy - dy));
            float p02 = get_gray(tex2D<uchar4>(tex, fx + dx, fy - dy));
            float p10 = get_gray(tex2D<uchar4>(tex, fx - dx, fy));
            float p12 = get_gray(tex2D<uchar4>(tex, fx + dx, fy));
            float p20 = get_gray(tex2D<uchar4>(tex, fx - dx, fy + dy));
            float p21 = get_gray(tex2D<uchar4>(tex, fx,      fy + dy));
            float p22 = get_gray(tex2D<uchar4>(tex, fx + dx, fy + dy));

            // оператор превитта
            float Gx = (p02 + p12 + p22) - (p00 + p10 + p20);
            float Gy = (p20 + p21 + p22) - (p00 + p01 + p02);

            // интенсивность (амплитуда градиента)
            float val = sqrtf(Gx * Gx + Gy * Gy);

            // ограничение значений в диапазоне [0, 255]
            unsigned char res = (unsigned char)fminf(255.0f, val);

            out[y * w + x] = make_uchar4(res, res, res, 255);
        }
    }
}

uchar4* read_data(const char* filename, int *w_ptr, int *h_ptr) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) exit(0);
    fread(w_ptr, sizeof(int), 1, fp);
    fread(h_ptr, sizeof(int), 1, fp);

    int w = *w_ptr;
    int h = *h_ptr;

    uchar4 *buffer = (uchar4 *)malloc(sizeof(uchar4) * w * h);
    fread(buffer, sizeof(uchar4), w * h, fp);

    fclose(fp);
    return buffer; // возврат указателя
}

int main() {
    char input_file[256], output_file[256];
    if (scanf("%s %s", input_file, output_file) != 2) return 0;

    int w, h;
    uchar4* data = read_data(input_file, &w, &h);

    cudaArray* arr;
    cudaChannelFormatDesc ch = cudaCreateChannelDesc<uchar4>();
    CSC(cudaMallocArray(&arr, &ch, w, h));
    CSC(cudaMemcpy2DToArray(arr, 0, 0, data, w * sizeof(uchar4), w * sizeof(uchar4), h, cudaMemcpyHostToDevice));

    struct cudaResourceDesc resDesc;
    memset(&resDesc, 0, sizeof(resDesc));
    resDesc.resType = cudaResourceTypeArray;
    resDesc.res.array.array = arr;

    struct cudaTextureDesc texDesc;
    memset(&texDesc, 0, sizeof(texDesc));
    texDesc.addressMode[0] = cudaAddressModeClamp;
    texDesc.addressMode[1] = cudaAddressModeClamp;
    texDesc.filterMode = cudaFilterModePoint;
    texDesc.readMode = cudaReadModeElementType;
    texDesc.normalizedCoords = true;

    cudaTextureObject_t tex = 0;
    CSC(cudaCreateTextureObject(&tex, &resDesc, &texDesc, NULL));

    uchar4* dev_out;
    CSC(cudaMalloc(&dev_out, sizeof(uchar4) * w * h));

    kernel<<<dim3(16, 16), dim3(32, 32)>>>(tex, dev_out, w, h);
    CSC(cudaGetLastError());

    uchar4* output_data = (uchar4*)malloc(sizeof(uchar4) * w * h);
    CSC(cudaMemcpy(output_data, dev_out, sizeof(uchar4) * w * h, cudaMemcpyDeviceToHost));

    FILE* fp = fopen(output_file, "wb");
    fwrite(&w, sizeof(int), 1, fp);
    fwrite(&h, sizeof(int), 1, fp);
    fwrite(output_data, sizeof(uchar4), w * h, fp);
    fclose(fp);

    CSC(cudaDestroyTextureObject(tex));
    CSC(cudaFreeArray(arr));
    CSC(cudaFree(dev_out));
    free(data);
    free(output_data);

    return 0;
}