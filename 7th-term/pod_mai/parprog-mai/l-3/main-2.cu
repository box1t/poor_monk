#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <cfloat>

#define CSC(call)                                                   \
do {                                                                \
    cudaError_t res = call;                                         \
    if (res != cudaSuccess) {                                       \
        fprintf(stderr, "ERROR in %s:%d. Message: %s\n",            \
                __FILE__, __LINE__, cudaGetErrorString(res));       \
        exit(0);                                                    \
    }                                                               \
} while(0)

__constant__ float3 avgj[32];

__global__ void kernel(uchar4* data, int w, int h, int nc) {
    int idx = blockDim.x * blockIdx.x + threadIdx.x;
    int offsetx = blockDim.x * gridDim.x;

    for (int i = idx; i < w * h; i += offsetx) {
        uchar4 ps = data[i];
        float3 p = make_float3(ps.x, ps.y, ps.z);

        float s, max_s = -FLT_MAX;
        int max_idx = 0;

        for (int j = 0; j < nc; j++) {
            float dx = p.x - avgj[j].x;
            float dy = p.y - avgj[j].y;
            float dz = p.z - avgj[j].z;

            s = -(dx * dx + dy * dy + dz * dz);

            if (s > max_s) {
                max_s = s;
                max_idx = j;
            }
        }
        data[i].w = (unsigned char)max_idx;
    }
}

bool read_image(const std::string& path, int& w, int& h, std::vector<uchar4>& data) {
    FILE *fp = fopen(path.c_str(), "rb");
    if (!fp) return false;

    fread(&w, sizeof(int), 1, fp);
    fread(&h, sizeof(int), 1, fp);
    data.resize(w * h);
    fread(data.data(), sizeof(uchar4), w * h, fp);
    fclose(fp);
    return true;
}

bool write_image(const std::string& path, int w, int h, const std::vector<uchar4>& data) {
    FILE *fp = fopen(path.c_str(), "wb");
    if (!fp) return false;

    fwrite(&w, sizeof(int), 1, fp);
    fwrite(&h, sizeof(int), 1, fp);
    fwrite(data.data(), sizeof(uchar4), w * h, fp);
    fclose(fp);
    return true;
}

std::vector<float3> calculate_averages(const std::vector<uchar4>& data, int w, int nc) {
    std::vector<float3> averages(nc);
    for (int i = 0; i < nc; i++) {
        long long np;
        std::cin >> np;
        float3 current_avg = make_float3(0.0f, 0.0f, 0.0f);

        for (long long j = 0; j < np; j++) {
            int px, py;
            std::cin >> px >> py;
            uchar4 ps = data[py * w + px];
            current_avg.x += ps.x;
            current_avg.y += ps.y;
            current_avg.z += ps.z;
        }
        current_avg.x /= np;
        current_avg.y /= np;
        current_avg.z /= np;
        averages[i] = current_avg;
    }
    return averages;
}

void run_processing(std::vector<uchar4>& data, int w, int h, const std::vector<float3>& h_averages) {
    uchar4 *dev_data;
    size_t size = sizeof(uchar4) * w * h;

    CSC(cudaMemcpyToSymbol(avgj, h_averages.data(), sizeof(float3) * h_averages.size()));

    CSC(cudaMalloc(&dev_data, size));
    CSC(cudaMemcpy(dev_data, data.data(), size, cudaMemcpyHostToDevice));

    kernel<<<1024, 1024>>>(dev_data, w, h, (int)h_averages.size());
    
    CSC(cudaGetLastError());
    CSC(cudaDeviceSynchronize());

    CSC(cudaMemcpy(data.data(), dev_data, size, cudaMemcpyDeviceToHost));
    CSC(cudaFree(dev_data));
}

int main() {
    std::string in_file, out_file;
    if (!(std::cin >> in_file >> out_file)) return 0;

    int w, h;
    std::vector<uchar4> image_data;

    int nc;
    std::cin >> nc;
    std::vector<float3> h_averages = calculate_averages(image_data, w, nc);

    run_processing(image_data, w, h, h_averages);



    return 0;
}