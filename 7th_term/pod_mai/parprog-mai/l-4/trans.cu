#include <stdio.h>
#include <assert.h>

#define CSC(call)                                                          \
  do {                                                                     \
    cudaError_t res = call;                                                \
    if (res != cudaSuccess) {                                              \
      fprintf(stderr, "ERROR in %s:%d. Message: %s\n", __FILE__, __LINE__, \
              cudaGetErrorString(res));                                    \
      exit(0);                                                             \
    }                                                                      \
  } while (0)


__global__ void kernel(float *src, float *dst, int n) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    int idy = blockIdx.y * blockDim.y + threadIdx.y;
    if (idx < n && idy < n) {
        dst[idx * n + idy] = src[idy * n + idx]; // меняем индексы местами
    }
}

int main() {
    int i, j, n = 1000;
    float *src = (float *)malloc(sizeof(float) * n * n); // 1-й массив. создаем м-цу размером n * n
    float *dst = (float *)malloc(sizeof(float) * n * n); // 2-й массив. создаем м-цу размером n * n

    for (i = 0; i < n*n; ++i) {
        src[i] = i; // скопировали, инициализировали src м-цу
    }

    float *dev_src, *dev_dst;
    CSC(cudaMalloc(&dev_src, sizeof(float) * n * n)); // выделили память под gpu под м-цу  
    CSC(cudaMalloc(&dev_dst, sizeof(float) * n * n)); // выделили память под gpu под м-цу
    CSC(cudaMemcpy(dev_src, src, sizeof(float) * n * n, cudaMemcpyHostToDevice)); // скопировали src м-цу на gpu
    CSC(cudaMemset(dev_dst, 0, sizeof(float) * n * n)); // проинициализировали gpu-шную м-цу нулями

    // поставим кусок кода, который будет замерять время работы программы

    cudaEvent_t start, stop;
    float time;
    CSC(cudaEventCreate(&start));
    CSC(cudaEventCreate(&stop));
    CSC(cudaEventRecord(start, 0)); // инициализируем событие до запуска нашего ядра

    // запускаем ядро

    dim3 blocks(32, 32);
    dim3 threads(32, 32);
    kernel<<< blocks, threads >>>(dev_src, dev_dst, n);

    CSC(cudaEventRecord(stop, 0)); 
    CSC(cudaEventSynchronize(stop)); 
    CSC(cudaEventElapsedTime(&time, start, stop));
    fprintf(stderr, "time = %f\n", time);

    CSC(cudaMemcpy(dst, dev_dst, sizeof(float) * n * n, cudaMemcpyDeviceToHost));
    CSC(cudaFree(dev_src));
    CSC(cudaFree(dev_dst));

    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            assert(src[j * n + i] == dst[i * n + j]);
        }
    }

    free(src);
    free(dst);
    return 0;
}