// Write a C program to sort an array by parity: placing even numbers in ascending order followed by odd numbers in descending order.
// без дополнительного массива

#include <stdio.h>

// =========================================================
// БЛОК 1: Разделение массива (Partition)
// Возвращает индекс, с которого начинаются нечетные числа.
// =========================================================
int partition_by_parity(int arr[], int arr_sz) {
    int left = 0;
    int right = arr_sz - 1;

    while (left < right) {
        // Ищем первое нечетное число слева
        while (left < right && arr[left] % 2 == 0) {
            left++;
        }
        // Ищем первое четное число справа
        while (left < right && arr[right] % 2 != 0) {
            right--;
        }
        // Меняем их местами
        if (left < right) {
            int temp = arr[left];
            arr[left] = arr[right];
            arr[right] = temp;
            left++;
            right--;
        }
    }
    // К этому моменту 'left' указывает на первый нечетный элемент 
    // (или на arr_sz, если все элементы четные)
    return left; 
}

// =========================================================
// БЛОК 2: Универсальная сортировка диапазона (Bubble Sort)
// Сортирует часть массива от start до end (включительно).
// Флаг ascending управляет направлением сортировки.
// =========================================================
void bubble_sort_range(int arr[], int start, int end, int ascending) {
    int n = end - start + 1; // Количество элементов в диапазоне
    
    for (int i = 0; i < n - 1; ++i) {
        for (int j = start; j < start + n - 1 - i; ++j) {
            
            int need_swap = 0;
            if (ascending) {
                if (arr[j] > arr[j + 1]) need_swap = 1; // По возрастанию
            } else {
                if (arr[j] < arr[j + 1]) need_swap = 1; // По убыванию
            }

            if (need_swap) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// =========================================================
// БЛОК 3: Главная функция (Дирижер)
// =========================================================
int main() {
    int arr[] = {5, 2, 8, 1, 9, 4, 3, 6};
    int arr_sz = sizeof(arr) / sizeof(arr[0]);

    // 1. Разделяем массив и получаем границу
    int odd_start_idx = partition_by_parity(arr, arr_sz);

    // 2. Сортируем четную часть (от 0 до odd_start_idx - 1) по возрастанию
    // Проверка (odd_start_idx > 0) нужна, если вдруг все числа нечетные
    if (odd_start_idx > 0) {
        bubble_sort_range(arr, 0, odd_start_idx - 1, 1); // 1 = ascending
    }

    // 3. Сортируем нечетную часть (от odd_start_idx до конца) по убыванию
    // Проверка (odd_start_idx < arr_sz) нужна, если вдруг все числа четные
    if (odd_start_idx < arr_sz) {
        bubble_sort_range(arr, odd_start_idx, arr_sz - 1, 0); // 0 = descending
    }

    // Вывод результата
    printf("Result: ");
    for (int i = 0; i < arr_sz; ++i) {
        printf("%d ", arr[i]);
    }
    // Ожидаемый вывод: 2 4 6 8 9 5 3 1 
    
    return 0;
}