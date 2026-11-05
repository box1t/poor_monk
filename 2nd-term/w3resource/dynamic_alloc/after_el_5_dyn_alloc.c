// Write a C program to create an array taking the elements after 
// the element value 5 from a given array of integers. 

#include <stdio.h>
#include <stdlib.h> // Для malloc и free

// Функция возвращает указатель на новый массив, а его размер записывает по указателю
int* take_elements_after_5_dyn(const int src[], int src_sz, int *dest_sz) {
    // 1. Выделяем максимально возможную память (в худшем случае все элементы после 5)
    // Это НЕ VLA, это память в куче (heap), она безопасна для больших размеров
    int *dest = (int*)malloc(src_sz * sizeof(int));
    
    if (dest == NULL) {
        *dest_sz = 0;
        return NULL; // Защита от нехватки памяти
    }

    int found_5 = 0;
    int dest_idx = 0;

    for (int i = 0; i < src_sz; ++i) {
        if (found_5) {
            dest[dest_idx++] = src[i];
        } 
        else if (src[i] == 5) {
            found_5 = 1;
        }
    }
    
    *dest_sz = dest_idx;
    return dest; // Возвращаем адрес начала массива
}

int main() {
    int arr[] = {1, 2, 5, 3, 4, 5, 6, 7};
    int arr_sz = sizeof(arr) / sizeof(arr[0]);
    
    int new_sz = 0;
    // 2. Получаем указатель на динамически созданный массив
    int *new_arr = take_elements_after_5_dyn(arr, arr_sz, &new_sz);

    if (new_arr != NULL) {
        printf("Dynamic array (size %d): [ ", new_sz);
        for (int i = 0; i < new_sz; ++i) {
            printf("%d ", new_arr[i]);
        }
        printf("]\n");
        
        // 3. ОСВОБОЖДАЕМ ПАМЯТЬ! Это главное правило при использовании malloc
        free(new_arr);
    }
    
    return 0;
}