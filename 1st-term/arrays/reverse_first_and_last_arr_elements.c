
/*
Reverse the first and last elements of an array.

Write a C program that reads an array of integers (length 8), 
replaces the 1st element with the 8th, 
the 2nd with the 7th and so on. 

Print the final array.

*/


/*
Нужно сохранить временное значение перед заменой и делать корректный swap.
Этот swap использует временные переменные для начала и для конца.
*/

#include <stdio.h>

int main() {
    int arr_size = 9;
    int arr[arr_size];

    for (int i = 0; i < arr_size; ++i) {
        scanf("%d", &arr[i]);
    }
    for (int i = 0; i < arr_size / 2; ++i) {
        printf("iter: [%d], start value of arr[i]: [%d]\n", i, arr[i]);
        
        int temp_elem = arr[arr_size - i - 1];
        int temp_starter = arr[i];

        arr[i] = temp_elem;
        arr[arr_size - i - 1] = temp_starter;
        
        printf("iter: [%d], end_value of arr[i]: [%d]\n", i, arr[i]);
    }
    printf("\n\n");    
    for (int i = 0; i < arr_size; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");
}
