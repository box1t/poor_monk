// Write a C program that accepts some text from the user and prints each word of that text on a separate line. вариант save_all

#include <stdio.h>
#include <ctype.h>

int main() {
    // Массив для хранения до 50 строк по 100 символов в каждой
    char all_text[50][100];
    int line_count = 0; // Счетчик прочитанных строк
    
    // Читаем строки, пока не достигнем лимита в 50 строк или конца файла
    while (line_count < 50 && fgets(all_text[line_count], sizeof(all_text[0]), stdin) != NULL) {
        
        // Обрабатываем текущую сохраненную строку
        for (int i = 0; all_text[line_count][i] != '\0'; ++i) {
            if (isspace((unsigned char)all_text[line_count][i])) {
                all_text[line_count][i] = '\n';
            }
        }
        
        line_count++; // Переходим к индексу следующей строки
    }
    
    // Теперь, когда весь ввод сохранен, выводим его
    for (int i = 0; i < line_count; ++i) {
        printf("%s", all_text[i]);
    }
    
    return 0;
}