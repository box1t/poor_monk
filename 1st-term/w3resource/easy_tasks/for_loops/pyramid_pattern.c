// Write a program in C to make a pyramid pattern with numbers increased by 1. 

#include <stdio.h>

int main() {
    int rows;
    int number = 1;

    printf("Input number of rows : ");  
    scanf("%d", &rows);
    int spc = rows;

    for (int i = 1; i <= rows; i++) {  // Start a loop to generate rows.
        for (int k = spc; k >= 0; k--) {  // Loop to print spaces before the numbers.
            printf(" ");
        }

        for (int j = 1; j <= i; j++) {
            printf("%d ", number++);
        }

        printf("\n");
        spc--;
    }
    return 0;
}