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

// Write a C program to count blanks, tabs, and newlines in input text.

#include <stdio.h>
#include <string.h>

int main() {
    char str1[100];
    fgets(str1, sizeof(str1), stdin);
    int cnt_blanks = 0, cnt_tabs = 0, cnt_newlines = 0;
    for (int i = 0; str1[i] != '\0'; ++i) {
        if (str1[i] == ' ') {
            cnt_blanks++;
        }
        if (str1[i] == '\t') {
            cnt_tabs++;
        }
        if (str1[i] == '\n') {
            cnt_newlines++;
        }
    }
    printf("%d\n%d\n%d\n", cnt_blanks, cnt_tabs, cnt_newlines);
}
