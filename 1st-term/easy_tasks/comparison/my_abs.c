
// Write a C program to remove any negative sign in front of a number.

#include <stdio.h>

int main() {
    int negative_number = -254;
    if (negative_number < 0) {
        negative_number = 0 - negative_number;
    }
    printf("%d", negative_number);
}