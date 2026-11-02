// Write a C program to check if a given integer is a power of three.

#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    if (n <= 0) {
        printf("no");
        return 0;
    }

    while (n % 3 == 0) {
        n /= 3;
    }

    if (n == 1) {
        printf("yes");
    } else {
        printf("no");
    }
}