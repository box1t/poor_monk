// Write a C program to copy a string and convert all lowercase letters to uppercase while counting the characters.
#include <stdio.h>

int main() {
    char str1[100];
    char str2[100];
    int count = 0;

    printf("Enter a string: ");
    fgets(str1, sizeof(str1), stdin);

    while (str1[count] != '\0') {

        if (str1[count] >= 'a' && str1[count] <= 'z') {
            str2[count] = str1[count] - ('a' - 'A');
        } else {
            str2[count] = str1[count];
        }

        count++;
    }

    str2[count] = '\0';

    printf("Converted string: %s", str2);
    printf("Characters copied: %d\n", count);

    return 0;
}