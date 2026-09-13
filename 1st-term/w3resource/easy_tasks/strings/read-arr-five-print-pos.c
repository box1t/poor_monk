
// Write a C program to read an array of length 5 and print the position and value of the array elements of value less than 5.

/*
1.
Выражение в условной ветке на сравнение i элемента массива с 5


2.
Ввод-вывод сканф без ссылки массива
Печать
*/

/*
read != fill?
реши обе задачи.

*/

/*
верно ли я понимаю, что
- в первом цикле массив пуст, свободен на 5 инт вперед.
- условие цикла некорретно из-за \0, поскольку на старте оно уже выполняется
---
первый цикл я пофиксил.
второй тоже, внимательно прочитав условие.

почему условие i != '\0' не срабатывало корректно?


int main() {
    int arr[5];
    for (size_t i = 0; i != '\0'; ++i) {
        scanf("%d", &arr[i]);
    }
    int el_pos;
    for (size_t i = 0; i != '\0'; ++i) {
        if (arr[i] < 5) {
            el_pos = i;
            printf("el_[%d]::pos_[%d]\n\n", arr[i], el_pos);
        }
    }
}
*/

#include <stdio.h>

int main() {
    int arr[5];
    for (size_t i = 0; i < 5; ++i) {
        scanf("%d", &arr[i]);
    }
    int el_pos;
    for (size_t i = 0; i < 5; ++i) {
        if (arr[i] < 5) {
            el_pos = i;
            printf("el_[%d]::pos_[%d]\n\n", arr[i], el_pos);
        }
    }
}