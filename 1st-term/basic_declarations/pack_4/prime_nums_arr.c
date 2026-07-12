// Write a C program to print prime numbers between 1 and 300, formatted in a table with a fixed number of columns.

#include <stdio.h>

int main() {
    int count = 0;

    for (int num = 2; num <= 300; num++) {
        int isPrime = 1;

        for (int i = 2; i * i <= num; i++) {
            if (num % i == 0) {
                isPrime = 0;
                break;
            }
        }

        if (isPrime) {
            printf("%5d", num);
            count++;

            if (count % 5 == 0) {
                printf("\n");
            }
        }
    }

    return 0;
}