// Write a C program to find prime numbers that are less than or equal to a given integer.

#include <stdio.h>

int isPrime(int num) {
    if (num < 2) {
        return 0;
    }
    // Делители любого числа всегда идут парами
    // в каждой паре одно число меньше или равно квадратному корню из числа, а другое — больше или равно
    // Если бы у числа был делитель больше его квадратного корня, 
    // то у него обязательно был бы и соответствующий ему делитель меньше квадратного корня, который мы уже проверили бы ранее
    for (int i = 2; i * i <= num; ++i) {
        if (num % i == 0) { // Это условие if срабатывает как раз тогда, когда число делится на что-то еще, а значит, оно НЕ простое
            return 0;
        }
    }
    return 1;
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 2; i <= n; ++i) {
        if (isPrime(i)) {
            printf("%d ", i);
        }
    }
    return 0;
}