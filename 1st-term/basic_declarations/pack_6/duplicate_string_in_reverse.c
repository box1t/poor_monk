// Write a C program to duplicate a string in reverse order and count the characters copied.

#include <stdio.h>

int main() {
    char str1[100];
    char str2[100];
    int length = 0;
    int count = 0;

    printf("Enter a string: ");
    fgets(str1, sizeof(str1), stdin);

    // Убираем символ новой строки, если он есть
    while (str1[length] != '\0') {
        if (str1[length] == '\n') {
            str1[length] = '\0';
            break;
        }
        length++;
    }

    // Если '\n' не было, находим длину строки
    while (str1[length] != '\0') {
        length++;
    }

    // Копирование в обратном порядке
    for (int i = length - 1; i >= 0; i--) {
        str2[count] = str1[i];
        count++;
    }

    str2[count] = '\0';

    printf("Reversed copy: %s\n", str2);
    printf("Characters copied: %d\n", count);

    return 0;
}