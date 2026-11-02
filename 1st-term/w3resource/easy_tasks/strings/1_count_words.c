// Write a program in C to count the total number of words in a string.

#include <stdio.h>
#include <ctype.h>

/*
Для компилятора запись str[i] и запись *(str + i) — это абсолютно одно и то же. 
Индекс i — это просто «синтаксический сахар» (удобная оболочка) для арифметики указателей.
*/

int count_words(char* str) {
    
    int count = 0;
    int in_word = 0;
    int i = 0;
    if (str == NULL) { // NULL — это макрос для указателей (адрес памяти 0). 
        // Сравнивать с ним символ (char) некорректно, хотя компилятор может это "проглотить", превратив NULL в обычный ноль. 
        return 0;
    }
    while (str[i] != '\0') { // *str != '\0'
        if (isspace((unsigned char)str[i])) { // isspace(... *str) Мы читаем символ, на который сейчас смотрит указатель. 
            in_word = 0;
        }
        else {
            if (in_word == 0) {
                in_word = 1;
                count++;
            }
            
        }
        i++; // str++
        // В версии с i мы увеличиваем счетчик шагов. В версии с указателем мы физически сдвигаем сам указатель на 1 байт вправо в памяти.
    }
    return count;
}

int main() {

    char str[] = " 123 456 ";
    printf("[%d] words in str", count_words(str));
}
