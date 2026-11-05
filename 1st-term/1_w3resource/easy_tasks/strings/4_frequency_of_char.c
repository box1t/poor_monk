// Write a program in C to find the maximum frequency of character in a string.

#include <stdio.h>
#include <ctype.h>

int main() {

    char str1[] = " 123 456 ";
    char str2[] = "123 456 ";

    int flag = 0;
    int max_count = 0;
    char max_symbol;

    for (int i = 0; str1[i] != '\0'; ++i) {
        int count = 0;
        
        for (int j = 0; j < i; ++j) {
            if (str1[i] == str1[j]) {
                flag = 1;
                break;
            }
        }
        if (!flag) {
            for (int j = 0; str1[j] != '\0'; ++j) {
                if (str1[i] == str1[j]) {
                    count++;
                }
                if (count > max_count && !isspace(str1[j])) {
                    max_count = count;
                    max_symbol = str1[j];
                }
            }   
        }
    }
    printf("max symbol is '%c'\nits ascii value is %d\nmax frequency is %d\n", max_symbol, max_symbol, max_count);

}
