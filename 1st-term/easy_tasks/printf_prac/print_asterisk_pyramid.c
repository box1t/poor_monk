
/*
Write a C program to display the pattern as a pyramid using asterisks, 
with each row containing an odd number of asterisks.
*/

/*
1. Задаем циклом некоторое число символов под печать.
Поскольку рисунок двумерный, у него измеримы строки и столбцы.
Цикл по строкам, по столбцам.
Но верно ли я понимаю, что сначала печатаются все столбцы, поскольку для подсчета приоритетно локальное значение?

*/

#include <stdio.h>

int main() {
    int pyramid_size = 10;
    for (int row = 0; row < pyramid_size; ++row) {
        for (int column = 1; column <= pyramid_size - row; ++column) {
            printf(" ");
        }
        for (int column = 1; column <= 2 * row - 1; ++column) {
            printf(" * ");
        }
        printf("\n\t");
    }
    printf("\n\n");
}

