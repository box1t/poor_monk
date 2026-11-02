// Write a C program to rotate the elements of a given array of integers (length sz) in the left direction and return the updated array. 

#include <stdio.h>

void rotate_left_universal(int arr[], int size) {
    if (size <= 1) return; // Сдвигать массив из 0 или 1 элемента бессмысленно

    int temp = arr[0]; // Сохраняем первый элемент
    
    // Сдвигаем все элементы от 1 до size-1 влево на 1 позицию
    for (int i = 0; i < size - 1; i++) {
        arr[i] = arr[i + 1];
    }
    
    // Помещаем сохраненный элемент в конец
    arr[size - 1] = temp;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6}; // Теперь длина 6
    int sz = sizeof(arr) / sizeof(arr[0]); // Вычисляем размер в main!
    
    printf("До: ");
    for(int i=0; i<sz; i++) printf("%d ", arr[i]);
    printf("\n");
    
    rotate_left_universal(arr, sz);
    
    printf("После: ");
    for(int i=0; i<sz; i++) printf("%d ", arr[i]);
    printf("\n");
    
    return 0;
}