// Write a program in C to compare two strings without using string library functions. 

#include <stdio.h>

int main() {

    char str1[] = " 123 456 ";
    char str2[] = "123 456 ";
    int flag = 1;
    int sz1 = sizeof(str1) / sizeof(str1[0]);
    int sz2 = sizeof(str2) / sizeof(str2[0]);

    if (sz1 != sz2) {
        flag = 0;
    }
    else {
        for (int i = 0; str1[i] != '\0' /*|| str2[i] != '\0' */; ++i) {
            if (str1[i] != str2[i]) {       
                flag = 0;
                break;
            }
        }
    }
    if (flag == 1) {
        printf("strs are equal");
    }
    else {
        printf("strs are not equal");
    }
}
