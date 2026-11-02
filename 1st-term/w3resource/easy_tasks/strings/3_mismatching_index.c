// Write a C program to compare two strings and output the index of the first mismatching character, if any.

#include <stdio.h>

int main() {

    char str1[] = " 123 456 ";
    char str2[] = "123 456 ";
    int flag = 1;

    for (int i = 0; str1[i] != '\0' || str2[i] != '\0'; ++i) {
        if (str1[i] != str2[i]) {       
            flag = 0;
            printf("mismatching index is %d\n", i);
            break;
        }
    }
    if (flag == 1) {
        printf("strs are equal");
    }
    else {
        printf("strs are not equal");
    }
}
