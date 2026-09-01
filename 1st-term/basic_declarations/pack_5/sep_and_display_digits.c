// Write a C program to separate and display the digits of an integer in original order using only arithmetic operators.

/*
Почему нельзя просто использовать % 10?
Можно:
digit = num % 10;
Но это даст цифры справа налево.

в этой задаче требуется разделить число на цифры в обычном порядке.
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

    int divisor = 1; // делитель помогает получить левую цифру числа, отбрасывая дробную часть справа
    // Поиск самой старшей разрядной единицы 
    while (num / divisor >= 10) {
        divisor *= 10;
    }

    // Вывод цифр слева направо
    while (divisor > 0) {

        int digit = num / divisor; // делением получаем цифру слева

        printf("%d ", digit);

        num = num % divisor; // остатком убираем цифру слева, оставляя число справа

        divisor /= 10; // сдвигаем делитель на один разряд вправо
    }

    return 0;
}

