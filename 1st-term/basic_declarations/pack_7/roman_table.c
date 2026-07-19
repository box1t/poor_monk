// Write a C program to print a table of all the Roman numeral equivalents of decimal numbers in the range 1 to 50. 
#include <stdio.h>

int main() {

    int values[] = {
        50, 40, 10, 9, 5, 4, 1
    };

    char *symbols[] = {
        "L", "XL", "X", "IX", "V", "IV", "I"
    };

    printf("Decimal\tRoman\n");
    printf("----------------\n");

    for (int num = 1; num <= 50; num++) {

        int number = num;

        printf("%d\t", num);

        for (int i = 0; i < 7; i++) {

            while (number >= values[i]) {

                printf("%s", symbols[i]);

                number -= values[i];
            }
        }

        printf("\n");
    }

    return 0;
}