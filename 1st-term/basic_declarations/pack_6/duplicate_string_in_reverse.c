// Write a C program to duplicate a string in reverse order and count the characters copied.

#include <stdio.h>
#include <string.h>

int main() {
    char str1[100] = "12345akrab";
    char str2[100];
    //fgets(str2, sizeof(str2), stdin);
    size_t count = 0;
    size_t j = 0;
    for (size_t i = strlen(str1) - 1; i >= 0; --i) {
        str2[j] = str1[i];
        count++;
        j++;
    }
    str2[j] = '\0';
    printf("Перевернутая строка: %s\n", str2);
    printf("Скопировано символов: %zu\n", count); // %zu - спецификатор для size_t
}
