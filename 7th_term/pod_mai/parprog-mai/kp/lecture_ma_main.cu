#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cuda_runtime.h>
#include <cuda_gl_interop.h>

// макрос для безопасных вызовов

#define CSC(call)                   \
do{                                 \
    cudaError_t status = call;      \
    if (status != cudaSuccess) {    \
        fprintf(stderr, "ERROR is %s:%d. Message: %s\n", __FILE__, __LINE__, cudaGetErrorString(status)); \
        exit(0);                    \
    }                               \
} while(0)

// функция анимации. значение double будет сопоставлено с цветом
// с каждым пикселом экрана сопоставим 1 точку в вещественном пр-ве, 
// вычислим значение ф-ции, сопоставим ф-ции цвет.


// обозначим размер окна
const int w = 1024;
const int h = 748;

// обозначим центр окна
const double xc = 0.0, yc = 0.0, sx = 5.0, sy = sx * h / w, minf = -3.0, maxf = 3.0;
// отрисуем на экране следующую область: [-sx, sx], [-sy, sy]   



__device__ double fun(double x, double y, double t) {
    return sin(x*x +t) + cos(y*y + 0.6*t) + sin(x*x + y*y + 0.3*t);
}

// перейдем от координат пикселей к координатам вещественным

// но как нам перейти от i с диапазоном [0, w] к [-sx, sx] ?

// i = [0, w - 1]
__device__ double fun(int x, int y, int t) {
    double x = 2.0 * i / (w - 1.0) - 1.0;
    double y = 2.0 * j / (h - 1.0) - 1.0;
    return fun(xc + x * sx, yc + y * sy, t);
}

// для работы из-под CUDA
struct cudaGraphicsResource *res;
// буфер в opengl 
GLuint vbo;

__global__ void kernel(uchar4 *data, double t) {
    int idx = blockDim.x * blockIdx.x + threadIdx.x;
    int idy = blockDim.y * blockIdx.y + threadIdx.y;
    int offsetx = gridDim.x * blockDim.x;
    int offsety = gridDim.y * blockDim.y;
    int i, j;
    for (i = idx; i < w; i += offsetx)
        for (j = idy; j < h; j += offsety) {
            double f = (fun(i, j, t) - minf) / (maxf - minf); // [0, 1]
            data[j * w + i] = make_uchar4(0, (int)(f*255), 0, 255);
        }
}

// основная ф.
void update() {
    // время - парам. анимации
    static double t = 0.0;
    uchar4 *data;
    size_t size;
    // отображение буфера в контекст cuda
    cudaGraphicsMapResources(1, &res, 0);
    // указатель на память буфера
    cudaGraphicsResourceGetMappedPointer((void**)&data, &size, res);
    kernel<<<dim3(32, 32), dim3(16, 16)>>>(data, t)l
    cudaGraphicsUnmapResources(1, &res, 0);
    // отрисовка окна
    glutPostRedisplay();
    t += 0.05;
}

void display() {
    // очистка происх. на экр.
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    // выводим всё что есть в активном буфере.
    // сам буфер активируем в другом месте
    glDrawPixels(w, h, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    // пока отрисовываем один буфер, другой выводится на экран
    glutSwapBuffers();
}

// обработка с клавиатуры
// на вход код клавиши
void keys(unsigned char key, int x, int y) {
    // по нажатии esc ресурс освободится
    if (key == 27) {
        cudaGraphicsUnsignedResource(res);
        glBindBuffer(1, vbo);
        glDeleteBuffers(1, &vbo);
        exit(0);
    }
}


// перейдем к main и рассмотрим работу оконного приложения
int main (int argc, char **argv) {
    // создаем окно
    glutInit(&argc, argv);
    // параллельная отрис.GLUT_DOUBLE: пока в один буфер отрисовываем, во второй пишем
    // это для того, чтобы не видеть отрисовку. 
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(w, h);
    glutCreateWindow("Hot Map");

    // создаем обработчики
    glutIdleFunc(update);
    glutDisplayFunc(display);
    glutKeyboardFunc(keys);

    // настроим вывод на экран.

    // зададим м-цу проекции
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho2d(0.0, (GLdouble)w, 0.0, (GLdouble)h); // двухмерное изображение с размерами

    // создаем общий буфер между cuda и opengl
    glewInit();
    // номер буфера, созданный с т.зр. opengl
    glGenBuffers(1, %vbo);
    // утверждаем, что буфер является активным
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER_ARB, vbo);
    // цветовые данные. NULL - указатель, откуда копируются данные, 
    // GL_DYNAMIC_DRAW - буфер изменяем
    glBufferData(GL_PIXEL_UNPACK_BUFFER_ARB, w*h*sizeof(uchar4), NULL, GL_DYNAMIC_DRAW);

    // регистрация буфера, cudaGraphicsMapFlagsWriteDiscard - буфер изменяем
    // изменяемость буфера влияет на отрисовку 
    CSC(cudaGraphicsGLRegister(&res, vbo, cudaGraphicsMapFlagsWriteDiscard));

    // основной цикл окна
    glutMainLoop();
    return 0;
}
