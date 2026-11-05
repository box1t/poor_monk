// Write a C program that accepts a string and counts the number of characters, words and lines.
// Слово начинается только тогда, когда мы переходим от пробельного символа к непробельному.

#include <stdio.h>

int main() {

    char str[1000];

    int characters = 0;
    int words = 0;
    int lines = 0;
    int inWord = 0;

    printf("Enter text (Ctrl+D/Ctrl+Z to finish):\n");

    /*
    // NULL — это про адреса в памяти (указатели). Означает «пустой адрес» или «ничего».
        Смысл: «Указатель ни на что не смотрит», «Память не выделена», «Функция не смогла вернуть адрес». (нет объекта)
        Значение: Обычно это 0 (или (void*)0).
        Где используется: В функциях, которые возвращают адреса (указатели). Например, fgets(), fopen(), malloc(), strstr().

    CTRL+D — это НЕ символ и НЕ буква. 
    Когда вы нажимаете CTRL+D в терминале, вы не вводите никакой символ в программу. Вы даете команду операционной системе: "Закрой поток ввода прямо сейчас".
    
    // EOF — это про чтение символов (потоки данных). Означает «конец файла» или «больше нет символов».
        Тип данных: Целое число (int). Это очень важно! Значение: Обычно это -1.
        Смысл: «Символов для чтения больше нет», «Мы дошли до конца».
        Где используется: В функциях, которые читают посимвольно и возвращают сам символ (в виде числа). Например, getchar(), fgetc(), scanf().
    
    */
    
    while (fgets(str, sizeof(str), stdin) != NULL) {

        lines++;

        for (int i = 0; str[i] != '\0'; i++) {

            // Считаем символы
            characters++;

            // Если встретили пробел, табуляцию или новую строку
            if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n') {
                inWord = 0;
            }
            else {
                // Начало нового слова
                if (inWord == 0) {
                    words++;
                    inWord = 1;
                }
            }
        }
    }

    printf("\nCharacters: %d\n", characters);
    printf("Words: %d\n", words);
    printf("Lines: %d\n", lines);

    return 0;
}

/*
#include <stdio.h>
#include <ctype.h>

int main() {
    char str[100];
    int chars = 0, words = 0, lines = 0;
    int i = 0;
    int in_word = 0;

    
    while (fgets(str, sizeof(str), stdin) != NULL) {
        ++lines;
        if (str[i] != '\0') {
            ++chars;
        }
        if (isspace(str[i])) {
            in_word = 0;
        }
        else {
            if (in_word == 0) {
                in_word = 1;
                ++words;
            }
        }
        ++i;
    }
}

*/