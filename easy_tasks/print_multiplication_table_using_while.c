
// Write a C program that prompts the user to enter a positive integer. Use a while loop to print the multiplication table for that number up to 10. 

#include <stdio.h>

int main() {
    printf("Type your value:");
    int val;
    scanf("%d", &val);
    int i = 1;
    while(i <= 10) {
        printf("(%d)--(%d)\n", i, val*i);
        ++i;
    }
}