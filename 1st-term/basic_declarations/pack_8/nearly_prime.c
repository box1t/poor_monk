// Write a C program to check if a given number is nearly prime number or not.
// Nearly prime numbers are a positive integer which is equal to the product of two prime numbers

#include <stdio.h>

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

    int n;

    printf("Enter a number: ");
    scanf("%d", &n);

    int nearlyPrime = 0;

    for (int i = 2; i * i <= n; i++) {

        if (n % i == 0) {

            int other = n / i;

            if (isPrime(i) && isPrime(other)) {
                nearlyPrime = 1;
                break;
            }
        }
    }

    if (nearlyPrime) {
        printf("%d is nearly prime.\n", n);
    } else {
        printf("%d is not nearly prime.\n", n);
    }

    return 0;
}