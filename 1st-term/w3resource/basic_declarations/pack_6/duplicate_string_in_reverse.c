// Write a C program to duplicate a string in reverse order and count the characters copied.

#include <stdio.h>
#include <string.h>

int main() {
    char str1[100] = "12345akrab";
    char str2[100];
    //fgets(str2, sizeof(str2), stdin);
    size_t count = 0;

    for (size_t i = strlen(str1) - 1; i >= 0; --i) {
        str2[count] = str1[i];
        count++;
    }

    str2[count] = '\0';
    printf("Перевернутая строка: %s\n", str2);
    printf("Скопировано символов: %zu\n", count); // %zu - спецификатор для size_t
}

/*

int main() {
    char str[20] = "12345";
    char dupl_str[20];
    int count = 0;

    int i = 0;
    while (str[i] != '\0') {
        i++;
    }
    
    // Начиная с последнего реального символа исходной строки, двигайся назад к самому первому символу.  
    for (int j = i - 1; j >= 0; --j) {
        dupl_str[count] = str[j]; // Каждый взятый символ клади в новую строку с самого начала, продвигаясь вперед,
        count++; // и считай, сколько символов ты уже переложил
    }
    dupl_str[count] = '\0';
    printf("%s", dupl_str);
    printf("%d - count ", count);
}

*/