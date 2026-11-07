// Write a C program to display the alphabet in both uppercase and lowercase with their ASCII values in hexadecimal.

#include <stdio.h>

int main() {
    char upper;
    char lower;

    // Print table headers
    printf("Uppercase |  Hex  | Lowercase |  Hex  \n");
    printf("---------------------------------------\n");

    // Loop through the alphabet
    // 'A' to 'Z' for uppercase, 'a' to 'z' for lowercase
    for (upper = 'A', lower = 'a'; upper <= 'Z'; upper++, lower++) {
        // %c prints the character
        // %02X prints the integer ASCII value as a 2-digit uppercase hexadecimal number
        printf("    %c     | 0x%02X  |     %c     | 0x%02X \n", upper, upper, lower, lower);
    }

    return 0;
}