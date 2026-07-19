/*
Write a C program to find all prime palindromes in the range of two given numbers x and y (5 <= x<y<= 1000,000,000).
A number is called a prime palindrome if the number is both a prime number and a palindrome.
*/
#include <stdio.h>

int isPalindrome(int n) {

    int original = n;
    int reversed = 0;

    while (n > 0) {
        reversed = reversed * 10 + n % 10;
        n /= 10;
    }

    return original == reversed;
}

int isPrime(int n) {

    if (n < 2) {
        return 0;
    }

    for (int i = 2; i * i <= n; i++) {

        if (n % i == 0) {
            return 0;
        }
    }

    return 1;
}

int main() {

    int x, y;

    printf("Enter x and y: ");
    scanf("%d %d", &x, &y);

    printf("Prime palindromes:\n");

    for (int i = x; i <= y; i++) {

        if (isPalindrome(i) && isPrime(i)) {
            printf("%d ", i);
        }
    }

    return 0;
}