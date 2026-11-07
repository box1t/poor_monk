// - нарисовать график функции на си

#include <stdio.h>
#include <math.h>

// Настройки "экрана" консоли
#define WIDTH  80   // Ширина в символах
#define HEIGHT 24   // Высота в строках

// Диапазон математических координат
#define X_MIN -10.0
#define X_MAX  10.0
#define Y_MIN -1.5
#define Y_MAX  1.5

// === ЗДЕСЬ ЗАДАЕТСЯ ФУНКЦИЯ ===
double f(double x) {
    return sin(x); 
    // Попробуйте заменить на: 
    // return x * x / 10.0 - 1.0; // Парабола
    // return cos(x);              // Косинус
}

int main() {
    printf("График функции y = sin(x)\n\n");

    // Проходим по строкам экрана СВЕРХУ ВНИЗ (от Y_MAX до Y_MIN)
    for (int row = HEIGHT - 1; row >= 0; row--) {
        
        // Проходим по столбцам экрана СЛЕВА НАПРАВО (от X_MIN до X_MAX)
        for (int col = 0; col < WIDTH; col++) {
            
            // 1. Преобразуем номер столбца (col) в математический X
            double x = X_MIN + (double)col / (WIDTH - 1) * (X_MAX - X_MIN);
            
            // 2. Вычисляем математический Y для этого X
            double y_func = f(x);
            
            // 3. Преобразуем математический Y обратно в номер строки экрана (row)
            // Формула: нормируем Y в диапазон [0, 1], умножаем на высоту и округляем
            int func_row = (int)((Y_MAX - y_func) / (Y_MAX - Y_MIN) * (HEIGHT - 1) + 0.5);
            
            // 4. Рисуем символ
            if (row == func_row) {
                printf("*");       // Точка графика функции
            } 
            else if (row == HEIGHT / 2 && col == WIDTH / 2) {
                printf("+");       // Начало координат (пересечение осей)
            } 
            else if (row == HEIGHT / 2) {
                printf("-");       // Ось X
            } 
            else if (col == WIDTH / 2) {
                printf("|");       // Ось Y
            } 
            else {
                printf(" ");       // Пустое пространство
            }
        }
        printf("\n"); // Переход на новую строку экрана
    }

    return 0;
}