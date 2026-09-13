
/*
Write a C program that prompts the user to input a series of integers 
until the user stops entering 0 using a while loop. 
Calculate and print the sum of all the positive integers entered. 
*/

#include <stdio.h>

int main() {
    int entry_number; // почему это ок и не инициализируется мусором?
    int sum_of_numbers = 0;

    while (entry_number) {
        scanf("%d", &entry_number);
        if (entry_number == 0) {
            break;
        }
        if (entry_number > 0) {
            sum_of_numbers += entry_number;
        }
    }
    printf("Sum of numbers: %d\n\n", sum_of_numbers);
}