// Write a program in C to convert a decimal number into binary without using an array.

#include <stdio.h>

int convert_to_binary(int num) {
    int arr[10];
    int i = 0;
    int res = 0;
    int count = 0;
    while (num > 0) {
        arr[i] = num % 2;
        num /= 2;
        count++;
    }
    for (int i = count; i >= 0; --i) {
        
    }
}

int main() {
    int num = 42;
    printf("[%d] is decimal for [%d]", num, convert_to_binary(num));
}
