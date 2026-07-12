// Write a C program to copy a string and simultaneously count the occurrences of a specified character.
#include <stdio.h>

int main() {
    char str1[100];
    char str2[100];
    char ch;
    int count = 0;
    int i = 0;

    printf("Enter a string: ");
    fgets(str1, sizeof(str1), stdin);

    printf("Enter character to search: ");
    scanf(" %c", &ch);

    while (str1[i] != '\0') {

        str2[i] = str1[i];

        if (str1[i] == ch) {
            count++;
        }

        i++;
    }

    str2[i] = '\0';

    printf("Copied string: %s", str2);
    printf("'%c' occurs %d times\n", ch, count);

    return 0;
}