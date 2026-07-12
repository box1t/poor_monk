// Write a C program to separate and display the digits of an integer using only arithmetic operators.

/*
Почему нельзя просто использовать % 10?
Можно:
digit = num % 10;
Но это даст цифры справа налево.

в этой задаче обычно требуется разделить число на цифры в обычном порядке.
Поэтому нужно сначала найти старший разряд.
*/

#include <stdio.h>

int main() {
    int num;

    printf("Enter an integer: ");
    scanf("%d", &num);

    // Обработка отрицательных чисел
    if (num < 0) {
        printf("- ");
        num = -num;
    }

    int divisor = 1; // делитель, который помогает "добраться" до первой (левой) цифры числа
    // Поиск самой старшей разрядной единицы
    while (num / divisor >= 10) {
        divisor *= 10;
    }

    // Вывод цифр слева направо
    while (divisor > 0) {

        int digit = num / divisor; // получаем цифру

        printf("%d ", digit);

        num = num % divisor; // убираем цифру слева (оператор % отбрасывает уже обработанную часть числа.)

        divisor /= 10; // уменьшаем делитель
    }

    return 0;
}

