
/*
Write a C program that calculates and prints the sum of cubes of even numbers up to a specified limit (e.g., 20) using a while loop. 
*/

#include <stdio.h>
#include <math.h>

int main() {
    int sum_of_numbers = 0;

    int based_number = 0;

    int exp = 3;
    while (based_number <= 20) {
        sum_of_numbers += pow(based_number, exp);
        based_number += 2;
    }
    printf("%d, ", sum_of_numbers);
}