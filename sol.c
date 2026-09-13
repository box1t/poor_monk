// Write a C program that accepts a string and counts the number of characters, words and lines.
// Слово начинается только тогда, когда мы переходим от пробельного символа к непробельному.


// int main() {
//     char str[20];
//     int chrs = 0, words = 0, lines = 0;
    
//     int in_word = 0;
//     while (fgets(str, sizeof(str), stdin) != NULL) {
//         ++lines;
//         for (int i = 0; str[i] != '\0'; ++i) {
//             ++chrs;
//             if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n') {
//                 in_word = 0;
//             }
//             else {
//                 if (in_word == 0) {
//                     in_word = 1;
//                     ++words;
//                 }
//             }
//         }
//     }
//     printf("\nCharacters: %d\n", chrs);
//     printf("Words: %d\n", words);
//     printf("Lines: %d\n", lines);
// }

#include <stdio.h>
#include <ctype.h> // для isspace()

int main() {
    // ✅ ИСПРАВЛЕНО: Выделяем память под строку
    char str[1024]; 
    
    printf("Enter text (Ctrl+D to end):\n");
    
    int chrs = 0, words = 0, lines = 0;
    int in_word = 0; // Флаг: находимся ли мы сейчас в слове
    
    // ✅ Читаем построчно до EOF (Ctrl+D в Linux, Ctrl+Z в Windows)
    while (fgets(str, sizeof(str), stdin) != NULL) {
        ++lines; // Каждая успешная строка fgets = одна линия
        
        int i = 0;
        while (str[i] != '\0') {
            // ✅ Подсчет символов (все, кроме переноса строки)
            if (str[i] != '\n') {
                ++chrs;
            }
            
            // ✅ Подсчет слов (переход пробел → непробел)
            if (isspace((unsigned char)str[i])) {
                in_word = 0;
            } else {
                if (in_word == 0) {
                    ++words;
                    in_word = 1;
                }
            }
            ++i;
        }
    }
    
    printf("\n--- Statistics ---\n");
    printf("Lines: %d\n", lines);
    printf("Words: %d\n", words);
    printf("Chars: %d\n", chrs);
    
    return 0;
}