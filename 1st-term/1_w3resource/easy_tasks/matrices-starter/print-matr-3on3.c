
/*
Write a program in C for a 2D array of size 3x3 and print the matrix. 
*/

#include <stdio.h>
#define ARR_SIZE 3

void init_matrix(int arr[][ARR_SIZE]) {
    int input_value = 0;
    for (int i = 0; i < ARR_SIZE; ++i) {
        printf("Введите значение для заполнения [%d] строки: ", i + 1);
        scanf("%d", &input_value);    
        for (int j = 0; j < ARR_SIZE; ++j) {
            arr[i][j] = input_value;
        }
    }
}

void print_matrix(int arr[][ARR_SIZE]) {
    for (int i = 0; i < ARR_SIZE; ++i) {
        for (int j = 0; j < ARR_SIZE; ++j) {
            if (j == 0) {
                printf("\t|%d\t", arr[i][j]);
            }
            else if (j == ARR_SIZE - 1) {
                printf("%d|", arr[i][j]);
            }
            else {
                printf("%d\t", arr[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n\n");
} 

int main() {
    int arr[ARR_SIZE][ARR_SIZE];
    init_matrix(arr);
    print_matrix(arr);

}