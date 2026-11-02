// Write a C program to create a new array from a given array of integers shifting all zeros to left direction.

#include <stdio.h>

void shift_zeros_to_left(int arr[], int arr_sz) {
    // Указатель, куда будем записывать следующий ненулевой элемент.
    // Начинаем с самого конца массива.
    int write_pos = arr_sz - 1;

    // Проходим по массиву справа налево
    for (int i = arr_sz - 1; i >= 0; --i) {
        if (arr[i] != 0) {
            // Если число не ноль, переносим его на позицию write_pos
            arr[write_pos] = arr[i];
            write_pos--; // Сдвигаем указатель влево для следующего ненулевого числа
        }
    }

    // Все элементы от индекса 0 до write_pos (включительно) должны быть нулями.
    // Заполняем оставшееся пространство нулями.
    while (write_pos >= 0) {
        arr[write_pos] = 0;
        write_pos--;
    }
}

int main() {
    int arr[] = {14, 0, 3, 2, 0, 1, 5, 0, 15};
    int arr_sz = sizeof(arr) / sizeof(arr[0]);
    
    for (int i = 0; i < arr_sz; ++i) {
        printf("%d ", arr[i]);
    }
}