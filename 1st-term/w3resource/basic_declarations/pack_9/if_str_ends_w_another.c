// Write a C program that accepts two strings and checks whether the second string is present in the last part of the first string.

#include <stdio.h>
#include <string.h>

int main() {

    char str1[100];
    char str2[100];

    printf("Enter first string: ");
    fgets(str1, sizeof(str1), stdin);

    printf("Enter second string: ");
    fgets(str2, sizeof(str2), stdin);
    // Убираем '\n' после fgets

    str1[strcspn(str1, "\n")] = '\0';
    str2[strcspn(str2, "\n")] = '\0';

    int len1 = strlen(str1);
    int len2 = strlen(str2);
    
    // Проверка 2: Сравниваем ВСЕ символы второй строки
    int found = 1; // Предполагаем, что строка найдена, пока не доказано обратное

    // Если вторая строка длиннее первой - она не может быть концом
    if (len2 > len1) {
        found = 0;
    }
    else {
        // Проверяем последние символы первой строки
        for (int i = 0; i < len2; i++) {
            // позиция, где должно начинаться совпадение
            if (str1[len1 - len2 + i] != str2[i]) {
                // Нашли первое несовпадение -> значит вся строка НЕ совпадает
                found = 0;
                break;
            }
        }
    }
    if (found) {
        printf("Second string is present at the end of first string\n");
    }
    else {
        printf("Second string is not present at the end\n");
    }
    return 0;
}