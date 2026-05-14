%%writefile main.cu
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cuda_runtime.h>
#include <cuda_gl_interop.h>

#define CSC(call)                   \
do{                                 \
    cudaError_t status = call;      \
    if (status != cudaSuccess) {    \
        fprintf(stderr, "ERROR is %s:%d. Message: %s\n", __FILE__, __LINE__, cudaGetErrorString(status)); \
        exit(0);                    \
    }                               \
} while(0)

const int w = 1024;
const int h = 748;
const double xc = 0.0, yc = 0.0, sx = 5.0, sy = 5.0 * h / w, minf = -3.0, maxf = 3.0;

struct cudaGraphicsResource *res;
GLuint vbo;

__device__ double fun(double x, double y, double t) {
    return sin(x*x + t) + cos(y*y + 0.6*t) + sin(x*x + y*y + 0.3*t);
}

__global__ void kernel(uchar4 *data, double t, int w, int h, double sx, double sy, double xc, double yc, double minf, double maxf) {
    int i = blockDim.x * blockIdx.x + threadIdx.x;
    int j = blockDim.y * blockIdx.y + threadIdx.y;
    int offsetx = gridDim.x * blockDim.x;
    int offsety = gridDim.y * blockDim.y;

    for (int x_idx = i; x_idx < w; x_idx += offsetx) {
        for (int y_idx = j; y_idx < h; y_idx += offsety) {
            double x_norm = 2.0 * x_idx / (w - 1.0) - 1.0;
            double y_norm = 2.0 * y_idx / (h - 1.0) - 1.0;
            double val = fun(xc + x_norm * sx, yc + y_norm * sy, t);
            
            double f = (val - minf) / (maxf - minf);
            if (f < 0.0) f = 0.0;
            if (f > 1.0) f = 1.0;
            
            data[(h - 1 - y_idx) * w + x_idx] = make_uchar4(0, (int)(f * 255), 0, 255);
        }
    }
}

void update() {
    static double t = 0.0;
    uchar4 *data;
    size_t size;
    CSC(cudaGraphicsMapResources(1, &res, 0));
    CSC(cudaGraphicsResourceGetMappedPointer((void**)&data, &size, res));
    
    dim3 threads(16, 16);
    dim3 blocks(32, 32);
    kernel<<<blocks, threads>>>(data, t, w, h, sx, sy, xc, yc, minf, maxf);
    
    CSC(cudaGraphicsUnmapResources(1, &res, 0));
    glutPostRedisplay();
    t += 0.05;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawPixels(w, h, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glutSwapBuffers();
}

void keys(unsigned char key, int x, int y) {
    if (key == 27) {
        cudaGraphicsUnregisterResource(res);
        glBindBuffer(GL_PIXEL_UNPACK_BUFFER_ARB, 0);
        glDeleteBuffers(1, &vbo);
        exit(0);
    }
}

int main (int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(w, h);
    glutCreateWindow("Hot Map");

    glutIdleFunc(update);
    glutDisplayFunc(display);
    glutKeyboardFunc(keys);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, w, 0.0, h);

    glewInit();
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER_ARB, vbo);
    glBufferData(GL_PIXEL_UNPACK_BUFFER_ARB, w * h * sizeof(uchar4), NULL, GL_DYNAMIC_DRAW);

    CSC(cudaGraphicsGLRegisterBuffer(&res, vbo, cudaGraphicsMapFlagsWriteDiscard));

    glutMainLoop();
    return 0;
}