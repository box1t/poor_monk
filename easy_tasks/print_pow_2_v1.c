
// Write a C program that prints the powers of 2 table for the powers 0 to 10, both positive and negative.

#include <stdio.h>
#include <math.h>

/*
Варианты улучшения:
1) форматирование заголовка таблицы
2) Форматирование спецификаторов (задание ширины), выбор другого для size_t

Варианты ускорения:
1) (Только для степеней двойки) Битовые сдвиги.
*/

int main() {
    int base = 3;
    printf("=================\t=================\t=================\niteration\t\tpositive_degrees\tnegative_degrees\n");
    for (size_t exp = 0; exp <= 10; ++exp) {
        printf("(%ld)\t\t\t(%ld)\t\t\t(%f)\n", exp, (long int)pow(base, exp), (1 / pow(base, exp)));
    }
}
