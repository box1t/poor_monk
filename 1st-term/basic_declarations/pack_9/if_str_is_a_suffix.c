// Write a C program to check if one string is a suffix of another using pointer comparisons.
#include <stdio.h>
#include <string.h>

int main() {

    char str1[100];
    char str2[100];

    printf("Enter first string: ");
    fgets(str1, sizeof(str1), stdin);

    printf("Enter second string: ");
    fgets(str2, sizeof(str2), stdin);

    // Удаляем символ '\n'
    str1[strcspn(str1, "\n")] = '\0';
    str2[strcspn(str2, "\n")] = '\0';

    int len1 = strlen(str1);
    int len2 = strlen(str2);

    if (len2 > len1) {
        printf("Second string is NOT a suffix.\n");
        return 0;
    }

    char *p1 = str1 + (len1 - len2);
    char *p2 = str2;

    while (*p2 != '\0') {

        if (*p1 != *p2) {
            printf("Second string is NOT a suffix.\n");
            return 0;
        }

        p1++;
        p2++;
    }

    printf("Second string IS a suffix.\n");

    return 0;
}