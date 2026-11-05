// перевод двоичного слова в азбуку Морзе

#include <stdio.h>
#include <string.h>

// Функция для перевода двоичной строки в код Морзе
void binary_to_morse(const char *binary, char *morse) {
    int j = 0; // Индекс для записи в строку morse
    
    // Проходим по каждому символу двоичной строки до конца ('\0')
    for (int i = 0; binary[i] != '\0'; i++) {
        if (binary[i] == '0') {
            morse[j] = '.';
            j++;
        } 
        else if (binary[i] == '1') {
            morse[j] = '-';
            j++;
        }
        // Если встретился любой другой символ (пробел, буква), мы его просто игнорируем.
        // Можно добавить else { morse[j++] = '?'; } для индикации ошибки.
    }
    
    // Обязательно добавляем нуль-терминатор в конец новой строки
    morse[j] = '\0';
}

int main() {
    char binary_input[256];
    char morse_output[256]; // Размер буфера должен быть не меньше размера ввода + 1

    printf("Введите двоичное слово (только 0 и 1): ");
    
    // Читаем строку, защищаясь от переполнения буфера
    if (scanf("%255s", binary_input) == 1) {
        
        // Вызываем функцию перевода
        binary_to_morse(binary_input, morse_output);
        
        printf("\n--- Результат ---\n");
        printf("Двоичный код : %s\n", binary_input);
        printf("Код Морзе    : %s\n", morse_output);
        
    } else {
        printf("Ошибка ввода.\n");
    }

    return 0;
}