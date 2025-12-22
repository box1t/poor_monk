%%writefile image.cu
#include <stdio.h>
#include <stdlib.h>

#define CSC(call)                                   \
do {                                          \
  cudaError_t res = call;                             \
  if (res != cudaSuccess) {                         \
    fprintf(stderr, "ERROR in %s:%d. Message: %s\n",      \
        __FILE__, __LINE__, cudaGetErrorString(res));   \
    exit(0);                                    \
  }                                           \
} while(0)

__global__ void kernel(cudaTextureObject_t tex, uchar4 *out, int w, int h) {
    int idx = blockDim.x * blockIdx.x + threadIdx.x;
    int idy = blockDim.y * blockIdx.y + threadIdx.y;
    int offsetx = blockDim.x * gridDim.x;
    int offsety = blockDim.y * gridDim.y;

    for (int y = idy; y < h; y += offsety) {
        for (int x = idx; x < w; x += offsetx) {
            uchar4 p = tex2D<uchar4>(tex, (float)x / w, (float)y / h);
            out[y * w + x] = make_uchar4(255 - p.x, 255 - p.y, 255 - p.z, p.w);
        }
    }
}

uchar4* read_data(const char* filename, int *w, int *h) {
    FILE *fp = fopen(filename, "rb");
    
    fread(w_ptr, sizeof(int), 1, fp);
    fread(h_ptr, sizeof(int), 1, fp);

    int w = *w_ptr; 
    int h = *h_ptr;

    uchar4 *buffer = (uchar4 *)malloc(sizeof(uchar4) * w * h);
    fread(buffer, sizeof(uchar4), w * h, fp);

    fclose(fp);
    return buffer;
}

void write_data(const char* filename, int w, int h, uchar4 *data) {
    FILE *fp = fopen(filename, "wb");
    fwrite(&w, sizeof(int), 1, fp);
    fwrite(&h, sizeof(int), 1, fp);
    fwrite(data, sizeof(uchar4), w * h, fp);
    fclose(fp);
}

cudaTextureObject_t create_texture(int w, int h, uchar4 *data, cudaArray **arr) {
    cudaChannelFormatDesc ch = cudaCreateChannelDesc<uchar4>();
    CSC(cudaMallocArray(arr, &ch, w, h));
    CSC(cudaMemcpy2DToArray(*arr, 0, 0, data, w * sizeof(uchar4), w * sizeof(uchar4), h, cudaMemcpyHostToDevice));

    struct cudaResourceDesc resDesc;
    memset(&resDesc, 0, sizeof(resDesc));
    resDesc.resType = cudaResourceTypeArray;
    resDesc.res.array.array = *arr;

    struct cudaTextureDesc texDesc;
    memset(&resDesc, 0, sizeof(resDesc));
    texDesc.addressMode[0] = cudaAddressModeWrap;
    texDesc.addressMode[1] = cudaAddressModeMirror; // Clamp
    texDesc.filterMode = cudaFilterModePoint;
    texDesc.readMode = cudaReadModeElementType;
    texDesc.normalizedCoords = true;

    cudaTextureObject_t tex = 0;
    CSC(cudaCreateTextureObject(&tex, &resDesc, &texDesc, NULL));
    return tex;
}

int main() {
    int w, h;
    uchar4 *data = read_data("wolf.data", &w, &h);
    
    cudaArray *arr;
    cudaTextureObject_t tex = create_texture(w, h, data, &arr);
    
    uchar4 *dev_out;
    size_t size = sizeof(uchar4) * w * h;
    CSC(cudaMalloc(&dev_out, size));

    kernel<<<dim3(16, 16), dim3(32, 32)>>>(tex, dev_out, w, h);
    CSC(cudaGetLastError());

    CSC(cudaMemcpy(data, dev_out, size, cudaMemcpyDeviceToHost));
    
    write_data("out.data", w, h, data);

    CSC(cudaDestroyTextureObject(tex));
    CSC(cudaFreeArray(arr));
    CSC(cudaFree(dev_out));

    free(data);
    return 0;
}