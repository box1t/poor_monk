#include <cuda_runtime.h>
#include <stdio.h>
#include <stdlib.h>

#define CSC(call)                                                          \
  do {                                                                     \
    cudaError_t res = call;                                                \
    if (res != cudaSuccess) {                                              \
      fprintf(stderr, "ERROR in %s:%d. Message: %s\n", __FILE__, __LINE__, \
              cudaGetErrorString(res));                                    \
      exit(0);                                                             \
    }                                                                      \
  } while (0)

const int k_alphabet_size = 1024;
const int k_max_threads = 1024;
const int k_max_blocks = 65535;

__global__ void histogram_kernel(const unsigned char* input, int* histogram, int n) {
  __shared__ int s_hist[k_alphabet_size];
  if (threadIdx.x < k_alphabet_size) s_hist[threadIdx.x] = 0;
  __syncthreads();

  int idx = blockIdx.x * blockDim.x + threadIdx.x;
  int stride = gridDim.x * blockDim.x;

  for (int i = idx; i < n; i += stride) {
    atomicAdd(&s_hist[input[i]], 1);
  }
  __syncthreads();

  if (threadIdx.x < k_alphabet_size) {
    atomicAdd(&histogram[threadIdx.x], s_hist[threadIdx.x]);
  }
}

__global__ void scan_kernel(const int* histogram, int* scan) {
  __shared__ int temp[k_alphabet_size];
  temp[threadIdx.x] = histogram[threadIdx.x];
  __syncthreads();

  int offset = 1;
  // какое ускорение благодаря такой схеме?
  for (int d = k_alphabet_size >> 1; d > 0; d >>= 1) {
    __syncthreads();
    if (threadIdx.x < d) {
      int ai = offset * (2 * threadIdx.x + 1) - 1;
      int bi = offset * (2 * threadIdx.x + 2) - 1;
      temp[bi] += temp[ai];
    }
    offset *= 2;
  }

  if (threadIdx.x == 0) temp[k_alphabet_size - 1] = 0;

  // редукция № 2: чередующая адресация с шаговым индексом и нерасходящейся ветвью
  for (int d = 1; d < k_alphabet_size; d *= 2) {
    offset >>= 1;
    __syncthreads();
    if (threadIdx.x < d) {
      int ai = offset * (2 * threadIdx.x + 1) - 1;
      int bi = offset * (2 * threadIdx.x + 2) - 1;
      int t = temp[ai];
      temp[ai] = temp[bi];
      temp[bi] += t;
    }
  }
  __syncthreads();
  scan[threadIdx.x] = temp[threadIdx.x];
}

__global__ void fill_output_kernel(unsigned char* output, const int* scan, int n) {
  int val = blockIdx.x;
  int start_idx = scan[val];
  int end_idx = (val == k_alphabet_size - 1) ? n : scan[val + 1];
  for (int i = start_idx + threadIdx.x; i < end_idx; i += blockDim.x) {
    output[i] = (unsigned char)val;
  }
}

void counting_sort(int n, unsigned char* h_input, unsigned char* h_output) {
  unsigned char *d_input, *d_output;
  int *d_histogram, *d_scan;

  CSC(cudaMalloc(&d_input, n * sizeof(unsigned char)));
  CSC(cudaMalloc(&d_output, n * sizeof(unsigned char)));
  CSC(cudaMalloc(&d_histogram, k_alphabet_size * sizeof(int)));
  CSC(cudaMalloc(&d_scan, k_alphabet_size * sizeof(int)));

  CSC(cudaMemset(d_histogram, 0, k_alphabet_size * sizeof(int)));
  CSC(cudaMemcpy(d_input, h_input, n * sizeof(unsigned char), cudaMemcpyHostToDevice));

  cudaEvent_t start, stop;
  float elapsedTime;
  CSC(cudaEventCreate(&start));
  CSC(cudaEventCreate(&stop));

  int blocks = (n + k_max_threads - 1) / k_max_threads;
  if (blocks > k_max_blocks) blocks = k_max_blocks;

  CSC(cudaEventRecord(start, 0));

  histogram_kernel<<<blocks, k_max_threads>>>(d_input, d_histogram, n);
  scan_kernel<<<1, k_alphabet_size>>>(d_histogram, d_scan);
  fill_output_kernel<<<k_alphabet_size, k_max_threads>>>(d_output, d_scan, n);

  CSC(cudaEventRecord(stop, 0));
  CSC(cudaEventSynchronize(stop));
  CSC(cudaEventElapsedTime(&elapsedTime, start, stop));

  fprintf(stderr, "GPU Kernel Execution Time: %.3f ms\n", elapsedTime);

  CSC(cudaMemcpy(h_output, d_output, n * sizeof(unsigned char), cudaMemcpyDeviceToHost));

  CSC(cudaFree(d_input)); CSC(cudaFree(d_output));
  CSC(cudaFree(d_histogram)); CSC(cudaFree(d_scan));
  CSC(cudaEventDestroy(start)); CSC(cudaEventDestroy(stop));
}

int main() {
  int n = 0;
  if (fread(&n, sizeof(int), 1, stdin) < 1) return 0;
  unsigned char* input = (unsigned char*)malloc(n);
  unsigned char* output = (unsigned char*)malloc(n);
  if (fread(input, 1, n, stdin) < (size_t)n) return 1;

  counting_sort(n, input, output);
  fwrite(output, 1, n, stdout);

  free(input); free(output);
  return 0;
}