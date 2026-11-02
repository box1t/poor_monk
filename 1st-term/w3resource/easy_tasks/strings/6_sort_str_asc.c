// Write a C program to sort a string array in ascending order.

#include <stdio.h>
#include <string.h>

void bubble_sort(char str[], int sz) {

    for (int i = 0; i < sz-1; ++i) {
        for (int j = 0; j < sz - 1 - i; ++j)
            if (str[j] > str[j + 1]) {
                char temp = str[j];
                str[j] = str[j + 1];
                str[j + 1] = temp; 
            }
    }
}

int main() {
    char str[] = "kraboed";
    int str_sz = sizeof(str) / sizeof(str[0]);
    bubble_sort(str, str_sz - 1);
    printf("%s", str);
}