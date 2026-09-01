// Write a C program to track and display all positions where the highest value occurs in the input list.

#include <stdio.h>

int main() {
    int n;
    // Считываем количество элементов
    if (scanf("%d", &n) != 1 || n <= 0) {
        return 0; 
    }

    int arr[n];
    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }

    int pos[n];       // Массив для хранения позиций (индексов) - track and display all positions
    int max = arr[0]; // Изначально максимум - первый элемент
    int count = 0;    // Счетчик найденных позиций максимального элемента

    for (int i = 0; i < n; ++i) {
        if (arr[i] > max) {
            // НАШЛИ НОВЫЙ МАКСИМУМ!
            max = arr[i];      // Обновляем максимум
            count = 0;         // Сбрасываем счетчик, старые позиции неактуальны, больше не нужны
            pos[count] = i + 1; // Запоминаем позицию (+1, чтобы считать с 1, а не с 0)
            // всё, что нам нужно, лежит в диапазоне от 0 до count - 1.
            count++;           // Увеличиваем счетчик
        }
        else if (arr[i] == max) {
            // НАШЛИ ЕЩЕ ОДНО ВХОЖДЕНИЕ ТЕКУЩЕГО МАКСИМУМА
            pos[count] = i + 1; // Запоминаем позицию, добавляя её в массив
            count++;            // Увеличиваем счетчик
        }
    }

    for (int i = 0; i < count; ++i) {
        printf("%d ", pos[i]);
    }
    printf("\n");

    return 0;
}