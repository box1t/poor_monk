// Write a C program that accepts some text from the user and prints each word of that text on a separate line.
#include <stdio.h>

int main() {
    char str[1000]; // Увеличил буфер, чтобы вместить больше текста за раз
    int inWord = 0; // 0 = мы вне слова, 1 = мы внутри слова

    // Читаем строки, пока не встретим конец файла (EOF)
    while (fgets(str, sizeof(str), stdin) != NULL) {
        
        for (int i = 0; str[i] != '\0'; ++i) {
            
            // Проверяем, является ли символ разделителем (пробел, таб, перенос строки, возврат каретки)
            if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n') {
                
                // Если мы были внутри слова, значит слово только что закончилось
                if (inWord) {
                    printf("\n"); // Переходим на новую строку для следующего слова
                    inWord = 0;   // Теперь мы снова вне слова
                }
            } else {
                // Это непробельный символ (буква, цифра и т.д.)
                printf("%c", str[i]);
                inWord = 1;
            }
        }
        // Защита на случай, если строка закончилась без \n, но мы были внутри слова
        if (inWord) {
            printf("\n");
            inWord = 0;
        }
    }

    return 0;
}