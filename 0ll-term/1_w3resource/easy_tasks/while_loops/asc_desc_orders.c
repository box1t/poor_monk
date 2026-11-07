
// Write a C program to print numbers from 0 to 10 and 10 to 0 using two while loops. 

#include <stdio.h>

int main() {
    int start_num = 0;
    int end_num = 10;

    printf("ASC ORDER: \n");
    while (start_num <= 10) {
        printf("[%d], ", start_num);
        ++start_num;
    }
    printf("\nDESC ORDER: \n");
    while (end_num >= 0) {
        printf("[%d], ", end_num);
        --end_num;
    }
    printf("\n\n\n");
}