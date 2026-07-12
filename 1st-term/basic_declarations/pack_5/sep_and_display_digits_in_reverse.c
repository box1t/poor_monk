// Write a C program to separate the digits of a number and display them in reverse order with spaces.
// Почему порядок получается обратным?
// Потому что мы каждый раз берём последнюю цифру числа.

#include <stdio.h>

int main() {
    int num;

    printf("Enter a number: ");
    scanf("%d", &num);

    if (num < 0) {
        num = -num;
        printf("- ");
    }

    if (num == 0) {
        printf("0");
    }
    else {
        while (num != 0) {
            printf("%d ", num % 10);
            num /= 10;
        }
    }

    return 0;
}