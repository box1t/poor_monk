// Write a function, that checks two arrays for equality.

#include <stdio.h>

// Функция возвращает true, если массивы равны, и false иначе
int areArraysEqual(const int arr1[], const int arr2[], int size) {
    for (int i = 0; i < size; i++) {
        if (arr1[i] != arr2[i]) {
            return 0; // Нашли различие — сразу выходим
        }
    }
    return 1; // Все элементы совпали
}

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