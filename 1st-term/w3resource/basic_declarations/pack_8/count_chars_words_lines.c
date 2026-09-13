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