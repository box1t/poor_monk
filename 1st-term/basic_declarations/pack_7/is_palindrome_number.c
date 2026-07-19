// Write a C program that determines whether or not number's a palindrome

#include <stdio.h>

int main() {

    int num;
    int original;
    int reversed = 0;

    printf("Enter a number: ");
    scanf("%d", &num);

    original = num;

    while (num > 0) {
        reversed = reversed * 10 + num % 10;
        num = num / 10;
    }

    if (original == reversed) {
        printf("Number is palindrome\n");
    }
    else {
        printf("Number is not palindrome\n");
    }

    return 0;
}