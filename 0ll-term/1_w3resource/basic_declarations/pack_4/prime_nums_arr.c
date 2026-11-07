// Write a C program to print prime numbers between 1 and 300, formatted in a table with a fixed number of columns.

#include <stdio.h>

int isPrime(int num) {
    if (num < 2) {
        return 0;
    }
    for (int i = 2; i * i <= num; ++i) {
        if (num % i == 0) {
            return 0;  // Нашли делитель -> сразу возвращаем "не простое"
        }
    }
    return 1;  // Делителей не нашли -> число простое
}

int main() {
    int count = 0; // переменная для форматирования столбцов
    int n;
    scanf("%d", &n);
    for (int num = 2; num <= n; num++) {
        if (isPrime(num)) {  // Просто вызываем функцию
            printf("%5d", num);
            count++;

            if (count % 5 == 0) {
                printf("\n");
            }
        }
    }

    return 0;
}