// Write a C program to rotate the elements of a given 
// array of integers (length N) in the left direction (on N positions) and return the updated array. 



// [1 2 3 4 5 6 7] -> [4 5 6 7 1 2 3] 

// 1. [1 2 3 4 5 6 7] 
// [3 2 1 | 7 6 5 4]
// 4 2 1 7 6 5 3
// 4 5 1 7 6 2 3
// 4 5 6 7 1 2 3





#include <stdio.h>

// Вспомогательная функция: переворачивает часть массива от индекса start до end
void reverse(int arr[], int start, int end) {
    while (start < end) {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        
        start++;
        end--;
    }
}

// 1 2 3 4 5 6 7 8 9
// сдвиг на 4
//- (0, 3)- 1 и 4
// 4 2 3 1
// (1, 2)
// 4 3 2 1
//--
//- (4, 8)- 5 и 9 
// 9 6 7 8 5
//- (5, 7)
// 9 8 7 6 5
//- (0, 8)- 4 и 5
// 4 3 2 1 9 8 7 6 5
// 5 3 2 1 9 8 7 6 4
// 5 6 2 1 9 8 7 3 4
// 5 6 7 1 9 8 2 3 4
// 5 6 7 8 9 1 2 3 4-finish


// Основная функция сдвига влево на n позиций
void rotate_left_n(int arr[], int sz, int n) {
    // Защита от пустого массива
    if (sz == 0) return;
    
    // КРИТИЧЕСКИ ВАЖНАЯ ОПТИМИЗАЦИЯ:
    // Если n больше длины массива, полный круг ничего не меняет.
    // Нам нужен только остаток от деления. 
    // Например, сдвиг на 10 позиций в массиве из 7 элементов = сдвиг на 3.
    n = n % sz;
    
    // Если после остатка n стало 0, сдвигать не нужно
    if (n == 0) return;

    // Шаг 1: Переворачиваем первые n элементов (индексы от 0 до n-1)
    reverse(arr, 0, n - 1);
    
    // Шаг 2: Переворачиваем оставшуюся часть (индексы от n до sz-1)
    reverse(arr, n, sz - 1);
    
    // Шаг 3: Переворачиваем весь массив целиком (индексы от 0 до sz-1)
    reverse(arr, 0, sz - 1);
}

// Функция для печати массива
void print_array(int arr[], int sz) {
    printf("[");
    for (int i = 0; i < sz; i++) {
        printf("%d", arr[i]);
        if (i < sz - 1) printf(", ");
    }
    printf("]\n");
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    int sz = sizeof(arr) / sizeof(arr[0]);
    int n = 3;

    printf("Исходный массив:   ");
    print_array(arr, sz);

    rotate_left_n(arr, sz, n);

    printf("Сдвиг влево на %d: ", n);
    print_array(arr, sz);
    
    // Тест с огромным n (например, 100)
    // 100 % 7 = 2. Должно сдвинуться как на 2 позиции.
    int arr2[] = {10, 20, 30, 40, 50};
    int sz2 = sizeof(arr2) / sizeof(arr2[0]);
    rotate_left_n(arr2, sz2, 100); 
    
    printf("Сдвиг массива из 5 эл. на 100 позиций: ");
    print_array(arr2, sz2);

    return 0;
}