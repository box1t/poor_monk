// Напишите программу на языке C, которая принимает от пользователя сумму в рублях и выдает минимальное количество купюр и монет для её выдачи
// Купюры: 1000, 500, 200, 100, 50, 10
// Монеты: 5, 2, 1

/*
1. Как инициализировать count_values[] на основе values[] согласно его размера без указания размера values[] вручную?
2. Как сделать проход в цикле for без указания вручную размера values ? достаточно функции size? или length? 
3. 

*/

#include <stdio.h>

int main() {
    int values[] = {1000, 500, 200, 100, 50, 10, 5, 2, 1};
    int n;
    scanf("%d", &n);
    int count_values[sizeof(values) / sizeof(values[0])] = {0};
    int sum_count_values = 0;
    int number = n;
    
    for (int i = 0; i < (sizeof(values) / sizeof(values[0])); ++i) {
        while (number >= values[i]) {
            number -= values[i];
            ++count_values[i];
        }
    }

    printf("Deposit sum: %d rub.\n", n);
    printf("----------------------\n");
    for (int i = 0; i < (sizeof(values) / sizeof(values[0])); ++i) {
        if (count_values[i] > 0) {
            printf("%4d x %d\n", values[i], count_values[i]);
            sum_count_values += count_values[i];
        }
    }
    printf("-----------------------\n");
    printf("units to withdraw: %d", sum_count_values);
}