// Write a program in C to extract a substring from a given string.

#include <stdio.h>

int main() {
    char str[] = "kedrovka";
    char substr[] = "";
    int str_sz = sizeof(str) / sizeof(str[0]) - 1;
    int idx_start = 5;
    int i = 0;
    while (idx_start != str_sz) {
        substr[i] = str[idx_start + i - 1];
        i++;
    }
    printf("%s", substr);
}