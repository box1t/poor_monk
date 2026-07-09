// Write a C program to print a p x q matrix of sequential numbers, where the numbers in each row are in reverse order. 
#include <stdio.h>

int main() {
    int p, q;

    scanf("%d %d", &p, &q);

    int matrix[p][q];

    int number = 1;

    // заполнение
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < q; j++) {
            matrix[i][j] = number;
            number++;
        }
    }

    // вывод в обратном порядке
    for (int i = 0; i < p; i++) {
        for (int j = q - 1; j >= 0; j--) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}