// Write a C program to copy a string and convert all lowercase letters to uppercase while counting the characters.
#include <stdio.h>
#include <ctype.h>

int main() {
    char str1[100];
    char str2[100];
    int count = 0;

    fgets(str1, sizeof(str1), stdin);
    while (str1[count] != '\0') {
        str2[count] = toupper((unsigned char)str1[count]);
        ++count;
    }
    if (count > 0 && str2[count - 1] == '\n') {
        --count;
    }
    printf("%s\nCount: %d", str2, count);
}
