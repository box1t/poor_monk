
// Write a C program to print the alphabet set in decimal and character form.

/*

для форматирования таблицы введи счетчик.
критерий переноса строки - превышение счетчиком заданного числа символов в строке.

*/

#include <stdio.h>

int main() {
    for (int i = 'A'; i <= 'Z'; ++i) {
        printf("(%d)-(%c)\n", i, i);
    }

    for (int i = 'a'; i <= 'z'; ++i) {
        printf("(%d)-(%c)\n", i, i);
    }
}
