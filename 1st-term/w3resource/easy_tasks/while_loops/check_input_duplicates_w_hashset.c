
/*

Write a C program that prompts the user to input a series of numbers
until they input a duplicate number.
Use a while loop to check for duplicates. 

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VALUE 1000000  // Максимальное число, которое можно ввести

bool hash_set[MAX_VALUE] = {false};  // Хэш-таблица

int main() {
    int input_var;

    while (1) {
        printf("Введите число: ");
        scanf("%d", &input_var);
        if (input_var < 0 || input_var >= MAX_VALUE) {
            printf("Число вне допустимого диапазона!\n");
            continue;
        }
        // Если число уже есть в hash_set, значит, это дубликат
        if (hash_set[input_var]) {
            printf("Найден дубликат: %d. Завершаем программу.\n", input_var);
            break;
        }
        // Добавляем число в hash_set
        hash_set[input_var] = true;
    }
    return 0;
}
