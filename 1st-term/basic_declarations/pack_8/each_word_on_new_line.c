// Write a C program that accepts some text from the user and prints each word of that text on a separate line.
#include <stdio.h>

int main() {

    char str[1000];
    int inWord = 0;

    printf("Enter text: ");
    fgets(str, sizeof(str), stdin);

    for (int i = 0; str[i] != '\0'; i++) {

        if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n') {

            if (inWord) {
                printf("\n");
                inWord = 0;
            }

        } else {

            printf("%c", str[i]);
            inWord = 1;

        }
    }

    return 0;
}