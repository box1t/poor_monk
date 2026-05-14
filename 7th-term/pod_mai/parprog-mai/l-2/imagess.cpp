#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <chrono> 

struct uchar4 {
    unsigned char x, y, z, w;
};

float get_gray(uchar4 p) {
    return 0.299f * p.x + 0.587f * p.y + 0.114f * p.z;
}

float get_pixel_mirror(uchar4* data, int w, int h, int x, int y) {
    if (x < 0) x = -x;
    if (x >= w) x = 2 * w - x - 1;
    if (y < 0) y = -y;
    if (y >= h) y = 2 * h - y - 1;
    return get_gray(data[y * w + x]);
}

void process_cpu(uchar4* in, uchar4* out, int w, int h) {
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {

            float p00 = get_pixel_mirror(in, w, h, x - 1, y - 1);
            float p01 = get_pixel_mirror(in, w, h, x,     y - 1);
            float p02 = get_pixel_mirror(in, w, h, x + 1, y - 1);
            float p10 = get_pixel_mirror(in, w, h, x - 1, y);
            float p12 = get_pixel_mirror(in, w, h, x + 1, y);
            float p20 = get_pixel_mirror(in, w, h, x - 1, y + 1);
            float p21 = get_pixel_mirror(in, w, h, x,     y + 1);
            float p22 = get_pixel_mirror(in, w, h, x + 1, y + 1);

            // Оператор Превитта
            float Gx = (p02 + p12 + p22) - (p00 + p10 + p20);
            float Gy = (p20 + p21 + p22) - (p00 + p01 + p02);

            float val = fabsf(Gx) + fabsf(Gy);
            if (val > 255.0f) val = 255.0f;
            unsigned char res = (unsigned char)val;

            out[y * w + x] = {res, res, res, 255};
        }
    }
}

int main() {
    int w, h;
    FILE *fp = fopen("in.data", "rb");
    if (!fp) return 1;
    fread(&w, sizeof(int), 1, fp);
    fread(&h, sizeof(int), 1, fp);
    uchar4 *data_in = (uchar4 *)malloc(sizeof(uchar4) * w * h);
    uchar4 *data_out = (uchar4 *)malloc(sizeof(uchar4) * w * h);
    fread(data_in, sizeof(uchar4), w * h, fp);
    fclose(fp);

    // Замер времени
    auto start = std::chrono::high_resolution_clock::now();
    
    process_cpu(data_in, data_out, w, h);
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float, std::milli> duration = end - start;

    printf("CPU Image size: %d x %d\n", w, h);
    printf("CPU Execution time: %.4f ms\n", duration.count());

    fp = fopen("out_cpu.data", "wb");
    fwrite(&w, sizeof(int), 1, fp);
    fwrite(&h, sizeof(int), 1, fp);
    fwrite(data_out, sizeof(uchar4), w * h, fp);
    fclose(fp);

    free(data_in);
    free(data_out);
    return 0;
}