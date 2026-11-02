// Write a C program to sort an array by parity: placing even numbers in ascending order followed by odd numbers in descending order.

#include <stdio.h>

void bubble_sort_asc(int arr[], int arr_sz) {
    for (int i = 0; i < arr_sz - 1; ++i) {
        for (int j = 0; j < arr_sz - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void bubble_sort_desc(int arr[], int arr_sz) {
    for (int i = 0; i < arr_sz - 1; ++i) {
        for (int j = 0; j < arr_sz - i - 1; ++j) {
            if (arr[j] < arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void sort_by_parity(int arr[], int new_arr[], int arr_sz) {
    int count_even = 0;
    int count_odd = 0;
    
    for (int i = 0; i < arr_sz; ++i) {
        if (arr[i] % 2 == 0) {
            new_arr[count_even] = arr[i];
            count_even++;
        }
    }
    bubble_sort_asc(new_arr, count_even);

    for (int j = arr_sz - 1; j >= 0; --j) {
        if (arr[j] % 2 != 0) {
            new_arr[count_even + count_odd] = arr[j];
            count_odd++;
        }
    }
    bubble_sort_desc(new_arr + count_even, count_odd);
}

int main() {
    int arr[] = {2, 2, 2, 8, 10, 12, 5, 0, 15};
    int arr_sz = sizeof(arr) / sizeof(arr[0]);
    int new_arr[arr_sz];
    sort_by_parity(arr, new_arr, arr_sz);
    for (int i = 0; i < arr_sz; ++i) {
        printf("%d ", new_arr[i]);
    }
}