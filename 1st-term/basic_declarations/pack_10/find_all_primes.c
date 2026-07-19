// Write a C program to find prime numbers that are less than or equal to a given integer.

#include <stdio.h>

int isPrime(int num) {
    if (num < 2) {
        return 0;
    }
    for (int i = 2; i * i <= num; ++i) {
        if (num % i == 0) {
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