// Write a C program to display a vertical histogram of integer values provided by the user.

#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    // Находим максимальное значение
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    // Рисуем вертикальную гистограмму
    for (int row = max; row > 0; row--) {
        for (int col = 0; col < n; col++) {
            if (arr[col] >= row) {
                printf(" * ");
            }
            else {
                printf("   ");
            }
        }
        printf("\n");
    }

    // Нижняя линия
    for (int i = 0; i < n; i++) {
        printf("---");
    }
    printf("\n");
    // Вывод значений под столбцами
    for (int i = 0; i < n; i++) {
        printf("%2d ", arr[i]);
    }

    return 0;
}