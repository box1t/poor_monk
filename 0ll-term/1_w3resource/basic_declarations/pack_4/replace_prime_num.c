// Write a C program to check each element in an array and, if it is a prime number, replace it with its square.

#include <stdio.h>

int isPrime(int num) {
    if (num < 2) {
        return 0;
    }
    for (int i = 2; i * i <= num; ++i) {
        if (num % i == 0) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }
    for (int i = 0; i < n; ++i) {
        if (isPrime(arr[i])) {
            arr[i] = arr[i] * arr[i];
        }
    }
    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
}