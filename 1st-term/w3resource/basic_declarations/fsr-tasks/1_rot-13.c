// Write a program that takes a printable character and prints its Rot13 encrypted version. Assume that the input is always a small character.
// It encrypts a message by shifting each character 13 letters in alphabetical order (modulo z).

// модульная арифметика обеспечивает корректный циклический сдвиг через весь алфавит

#include <stdio.h>

int main() {
    char c;
    
    printf("Enter a character: ");
    scanf(" %c", &c); // Пробел перед %c игнорирует предыдущие переводы строк
    
    // Rot13 для маленькой буквы
    if (c >= 'a' && c <= 'z') {
        c = 'a' + (c - 'a' + 13) % 26;
    }
    // Rot13 для большой буквы (на случай, если условие расширят)
    else if (c >= 'A' && c <= 'Z') {
        c = 'A' + (c - 'A' + 13) % 26;
    }
    // Не-буквы (цифры, знаки препинания) остаются без изменений
    
    printf("Rot13: %c\n", c);
    
    return 0;
}