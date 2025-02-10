
/*
Write a C program that accepts a string and counts the number of characters, words and lines.
*/

#include <stdio.h>
#include <ctype.h>

int main() {
    char string[] = "string\n\n";
    int words_counter = 0;
    int spaces_counter = 0;
    int lines_counter = 0;
    int chars_counter = 0;

    int in_word = 0;  

    for (int i = 0; string[i] != '\0'; ++i) {
        if (string[i] == '\n' || string[i] == '\t') {
            ++lines_counter;
        }
        if (string[i] == ' ') {
            +spaces_counter;
        }
        if (isalpha(string[i])) {
            ++chars_counter;
            if (!in_word) {
                ++words_counter;
                in_word = 1;
            }
        } else {
            in_word = 0;
        }
    }
    printf("spaces: %d\nlines: %d\ncharactes: %d\nwords: %d\n\n", spaces_counter, lines_counter, chars_counter, words_counter);
}