// Write a C program to determine the second highest value and its index from a set of integers.

#include <stdio.h>
#include <limits.h>

int main() {
    int n; // считываемое число
    int max = INT_MIN; // минимально возможное значение для типа int
    int second_max = INT_MIN;
    int max_pos = 0;
    int second_pos = 0;

    int pos = 0; // какое по счету число мы сейчас читаем

    while (scanf("%d", &n) == 1) { // Пытайся прочитать целое число. Если чтение прошло успешно (вернуло 1), выполняй цикл
        pos++; // увеличиваем счетчик позиции на 1 для каждого числа

        // Если прочитанное число больше максимума
        if (n > max) {
            // второе место (second_max) и его позиция (second_pos) получают те значения, которые до этого были у первого места
            second_max = max;
            second_pos = max_pos;

            // назначаем новый максимум
            max = n;
            max_pos = pos;
        }
        // (если число не побило главный рекорд), НО оно больше текущего результата на втором месте
        else if (n > second_max) {
            // Это число просто занимает второе место
            second_max = n;
            second_pos = pos;
        }
    }

    if (second_pos != 0) {
        printf("Second highest = %d\n", second_max);
        printf("Position = %d\n", second_pos);
    }
    else {
        printf("Not enough numbers");
    }

    return 0;
}