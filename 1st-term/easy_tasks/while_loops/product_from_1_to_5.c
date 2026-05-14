
// Write a C program that calculates the product of numbers from 1 to 5 using a while loop. 

#include <stdio.h>

int main() {
    int entry_num = 1;
    int product = 1;
    while (entry_num <= 5) {
        product *= entry_num;
        ++entry_num;
    }
    printf("%d\n\n", product);
}