// Write a C program to create a frequency table for all characters and identify the one with the highest frequency.

// O(n)
#include <stdio.h>
#include <ctype.h>

int main() {
    char str[] = " 123 456 ";
    
    // 1. Создаем массив для частот всех возможных ASCII символов (0-255)
    // и инициализируем его нулями
    int freq[256] = {0}; 

    /*
        У нас идеальная ситуация:

        Ключом является символ.
        Символ в C — это уже готовое число от 0 до 255.
        Количество возможных ключей (256) очень маленькое.
    */


    // 2. ОДИН проход по строке: заполняем таблицу частот
    for (int i = 0; str[i] != '\0'; ++i) {
        // Приводим к unsigned char, чтобы использовать как безопасный индекс 0-255
        freq[(unsigned char)str[i]]++; // идеальная, вырожденная форма хеш-таблицы - "прямая адресация" (direct addressing)
    }

    printf("%-12s %10s\n", "Symbol", "Frequency");
    printf("%-12s %10s\n", "------------", "----------");

    
    int max_count = 0;
    char max_symbol = '\0';

    // 3. Один проход по массиву частот (всего 256 итераций, независимо от длины строки!)
    for (int i = 0; i < 256; ++i) {
        if (freq[i] > 0) { // Если символ встречался хотя бы раз
            char current_char = (char)i;
            
            // Выводим в таблицу (можно добавить условие !isspace, если пробелы в таблице не нужны)
            printf("'%c'%-9s %10d\n", current_char, "", freq[i]);

            // Ищем максимум, игнорируя пробельные символы
            if (!isspace((unsigned char)current_char)) {
                if (freq[i] > max_count) {
                    max_count = freq[i];
                    max_symbol = current_char;
                }
            }
        }
    }

    if (max_symbol != '\0') {
        printf("\nmax symbol is '%c'\nits ascii value is %d\nmax frequency is %d\n", 
               max_symbol, (unsigned char)max_symbol, max_count);
    }

    return 0;
}