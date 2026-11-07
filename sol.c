// Write a C program to sort an array by parity: 
// placing even numbers followed by odd numbers.
// как решить без создания нового массива?

#include <stdio.h>




// void sort_by_parity(int arr[], int arr_sz) {

// }

int main() {
    int arr[] = {0, 0, 1, 2, 3, 0, 4, 0, 5, 0};
    int arr_sz = sizeof(arr) / sizeof(arr[0]);

    // sort_by_parity(arr, arr_sz);

    for (int i = 0; i < arr_sz; ++i) {
        printf("%d ", arr[i]);
    }
}

