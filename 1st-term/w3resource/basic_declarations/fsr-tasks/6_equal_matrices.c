#include <stdio.h>

#define ROWS 3
#define COLS 4

// Функция для сравнения двумерных массивов
int areMatricesEqual(const int m1[ROWS][COLS], const int m2[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (m1[i][j] != m2[i][j]) {
                return 0; // Нашли различие
            }
        }
    }
    return 1; // Все элементы совпали
}

int main() {
    int matrix1[ROWS][COLS] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };

    int matrix2[ROWS][COLS] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };

    int matrix3[ROWS][COLS] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 99}  // Отличается последний элемент
    };

    if (areMatricesEqual(matrix1, matrix2)) {
        printf("matrix1 and matrix2 are EQUAL\n");
    } else {
        printf("matrix1 and matrix2 are NOT equal\n");
    }

    if (areMatricesEqual(matrix1, matrix3)) {
        printf("matrix1 and matrix3 are EQUAL\n");
    } else {
        printf("matrix1 and matrix3 are NOT equal\n");
    }

    return 0;
}