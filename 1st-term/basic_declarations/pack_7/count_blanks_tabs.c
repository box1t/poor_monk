// Write a C program to count blanks, tabs, and newlines in input text.
#include <stdio.h>

int main() {

    int blanks = 0;
    int tabs = 0;
    int newlines = 0;

    int ch;

    printf("Enter text (Ctrl+D to finish):\n");

    while ((ch = getchar()) != EOF) {

        if (ch == ' ') {
            blanks++;
        }
        else if (ch == '\t') {
            tabs++;
        }
        else if (ch == '\n') {
            newlines++;
        }
    }

    printf("Blanks: %d\n", blanks);
    printf("Tabs: %d\n", tabs);
    printf("Newlines: %d\n", newlines);

    return 0;
}