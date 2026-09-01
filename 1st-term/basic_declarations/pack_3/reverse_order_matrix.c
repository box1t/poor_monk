// Write a C program to print a p x q matrix of sequential numbers, where the numbers in each row are in reverse order. 
#include <stdio.h>

int main() {
    int p, q;

    scanf("%d %d", &p, &q);

    int matrix[p][q]; // Создается пустая двумерная таблица

    int number = 1; // Создается переменная-счетчик

    // Заполнение таблицы по порядку 
    for (int i = 0; i < p; i++) { // внешний цикл (i) отвечает за строки (движется сверху вниз).
        for (int j = 0; j < q; j++) { // Внутренний цикл (j) отвечает за столбцы (движется слева направо, от 0 до q-1).
            matrix[i][j] = number; // В каждую ячейку matrix[i][j] кладется текущее значение number
            number++;
        }
    }

    // вывод таблицы на экран в обратном порядке  
    for (int i = 0; i < p; i++) { // Внешний цикл (i) по-прежнему идет сверху вниз по строкам
        for (int j = q - 1; j >= 0; j--) { // Внутренний цикл - Справа налево
            printf("%d ", matrix[i][j]);
        }
        printf("\n"); // переносит курсор на новую строку, чтобы начать печать следующей строки матрицы
    }

    return 0;
}