// Write a function, that checks two arrays for equality.

#include <stdio.h>

// предполагается равная длина массивов
// Функция возвращает true, если массивы равны, и false иначе
int areArraysEqual(const int arr1[], const int arr2[], int size) {
    for (int i = 0; i < size; i++) {
        if (arr1[i] != arr2[i]) {
            return 0; // Нашли различие — сразу выходим
        }
    }
    return 1; // Все элементы совпали
}
/*

int are_arrays_equal_for(int arr1[], int arr2[], int arr_sz1, int arr_sz2) {
    if (arr_sz1 != arr_sz2) {
        return 0;
    }
    for (int i = 0; i < arr_sz1; ++i) {
        if (arr1[i] != arr2[i]) {
            return 0;
        }
    }
    return 1;
}
int are_arrays_equal_while(int arr1[], int arr2[], int arr_sz) {
    int i = 0;
    while (arr1[i] == arr2[i]) {
        ++i;
    }
    if (i == arr_sz) {
        return 1;
    }
    return 0;
}


*/


int main() {
    int arr1[20] = {1, 2, 3, 5};
    int arr2[20] = {1, 2, 3, 4}; 
    int arr3[20] = {1, 2, 3, 5};

    int size = sizeof(arr1) / sizeof(arr1[0]);

    if (areArraysEqual(arr1, arr2, size)) {
        printf("arr1 and arr2 are equal\n");
    } else {
        printf("arr1 and arr2 are NOT equal\n");
    }

    if (areArraysEqual(arr1, arr3, size)) {
        printf("arr1 and arr3 are equal\n");
    } else {
        printf("arr1 and arr3 are NOT equal\n");
    }

    return 0;
}