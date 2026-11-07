// Write a C program to print the alphabet set in decimal and character form.

#include <stdio.h>

int main() {
    for (int i = 65; i <= 90; ++i) {
        printf("[%d-%c]\n", i,i);
    }
}