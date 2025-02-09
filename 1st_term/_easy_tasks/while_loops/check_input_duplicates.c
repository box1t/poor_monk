
/*

Write a C program that prompts the user to input a series of numbers
until they input a duplicate number.
Use a while loop to check for duplicates. 

*/

/*
Сначала проверяем, есть ли input_var в массиве.
Только после полной проверки добавляем в массив.
*/

/*

Идея:

1.
Завести доп. переменную для подсчета записанных чисел.
Проверять дубликаты циклом for только среди них.
Проверять заполнение массива превышением count его размера arr_size
Записывать числа в массив отдельно от for на позицию count.
Использовать break внутри while, а внутри for - return 0. (почему?)
Использовать неинициализированные массив и переменную input_var (почему?)

*/


#include <stdio.h>

int main() {
    const int arr_size = 10;
    int arr[arr_size] = {0};
    int count = 0;
    int input_var;

    while (1) {
        printf("Введите число: ");
        scanf("%d", &input_var);
        for (size_t i = 0; i < count; ++i) {
            if (arr[i] == input_var) {
                printf("Найден дубликат: %d. Завершаем программу.\n\n", input_var);
                return 0;
            }
        }
        if (count >= arr_size) {
            printf("Массив заполнен. Завершаем программу.\n\n");
            break;
        }
        arr[count] = input_var;
        ++count;
    }
    return 0;
}
