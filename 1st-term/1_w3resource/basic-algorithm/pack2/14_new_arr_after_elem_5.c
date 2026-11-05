// Write a C program to create an array taking the elements after the element value 5 from a given array of integers. 

#include <stdio.h>

// Функция возвращает количество реально скопированных элементов
int take_elements_after_5(int arr[], int arr_sz, int new_arr[]) {
    int found_5 = 0;   // Флаг: видели ли мы уже пятерку
    int new_count = 0; // Счетчик элементов в новом массиве

    for (int i = 0; i < arr_sz; ++i) {
        // Если пятерка уже была найдена, копируем текущий элемент
        if (found_5) {
            new_arr[new_count] = arr[i];
            new_count++;
        }
        
        // Если текущий элемент равен 5, включаем флаг для СЛЕДУЮЩИХ итераций
        if (arr[i] == 5) {
            found_5 = 1;
        }
    }
    
    return new_count; // Возвращаем реальный размер заполненной части
}

int main() {
    int arr[] = {14, 2, 3, 3, 18, 1, 5, 1, 15};
    int arr_sz = sizeof(arr) / sizeof(arr[0]);
    
    // Новый массив гарантированно не меньше исходного
    int new_arr[arr_sz]; 
    
    // Вызываем функцию и ПОЛУЧАЕМ реальный размер новых данных
    int actual_new_sz = take_elements_after_5(arr, arr_sz, new_arr);
    
    printf("Скопировано элементов: %d\n", actual_new_sz);
    printf("Результат: [ ");
    
    // Печатаем ТОЛЬКО реальное количество элементов, никакого мусора!
    for (int i = 0; i < actual_new_sz; ++i) {
        printf("%d ", new_arr[i]);
    }
    printf("]\n");
    
    return 0;
}