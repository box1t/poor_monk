// Write a C program to find the last non-zero digit of the factorial of a given positive integer.
// For example for 5!, the output will be "2" because 5! = 120, and 2 is the last nonzero digit of 120

#include <stdio.h>

int main() {

    int n;

    printf("Enter a positive integer: ");
    scanf("%d", &n);

    int result = 1;

    for (int i = 2; i <= n; i++) {

        result *= i;

        // удаляем конечные нули
        while (result % 10 == 0) {
            result /= 10;
        }

        // оставляем только последние цифры
        result %= 100000;
    }

    printf("Last non-zero digit of %d! is %d\n", 
           n, result % 10);

    return 0;
}
