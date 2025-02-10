
/*
Write a C program that implements a program to check if a given number is a palindrome using a while loop. 
*/

#include <stdio.h>
#include <math.h>

int main() {
    int entry_number = 12321;
    int original_number = entry_number;
    int remainder;
    int reversed_number = 0;

    entry_number = abs(entry_number);
    if (entry_number == 0) {
        printf("0 — палиндром.\n");
        return 0;
    }    

    while (entry_number > 0) {
        remainder = entry_number % 10;
        reversed_number = reversed_number * 10 + remainder;
        entry_number /= 10;
    }

    if (original_number == reversed_number) {
        printf("ARE palindromes.\n\n");
    } else {
        printf("ARE NOT palindromes.\n\n");
    }
}