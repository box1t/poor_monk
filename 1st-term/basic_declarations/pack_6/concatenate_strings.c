// concatenate two strings

#include <stdio.h>

int main() {
    char str1[100] = "Hello";
    char str2[] = " World";

    int i = 0;
    int j = 0;

    // Находим конец первой строки
    while (str1[i] != '\0') {
        i++;
    }

    // Копируем вторую строку в конец первой
    while (str2[j] != '\0') {
        str1[i] = str2[j];
        i++;
        j++;
    }

    // Добавляем конец строки
    str1[i] = '\0';

    printf("%s\n", str1);

    return 0;
}