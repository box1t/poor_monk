
/*
Write a C program that prompts the user to enter a positive integer. 
It then calculates and prints the factorial of that number using a while loop. 
*/

#include <stdio.h>

int main() {
    int input_var;
    int fact = 1;
    // int saved_value = input_var; 
    
    scanf("%d", &input_var);
    if (input_var < 0) {
        printf("Negative number entered. Factorial is undefined.\n");
        return 1;
    }
    
    int saved_value = input_var;
    while (input_var > 0) {
        fact *= input_var;
        --input_var;
    }

    printf("fact of %d is %d", saved_value, fact);
}