
// Write a C program that prints the powers of 2 table for the powers 0 to 10, both positive and negative.

#include <stdio.h>

int main() {
    printf("=======================================================\n");
    printf("iteration | positive_degrees | negative_degrees\n");
    printf("=======================================================\n");
    
    for (size_t exp = 0; exp <= 10; ++exp) {
        printf("%-9ld | %-16d | %.12f\n", exp, (1 << exp), 1.0 / (1 << exp));
    }

    printf("=======================================================\n");
    return 0;
}
