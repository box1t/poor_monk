// Write a C program to check each element in an array and, if it is a prime number, replace it with its square.
#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    int arr[n];

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    for (int i = 0; i < n; i++) {
        if (arr[i] < 2) {
            continue;
        }

        int is_prime = 1;

        for (int j = 2; j * j <= arr[i]; j++) {
            if (arr[i] % j == 0) {
                is_prime = 0;
                break;
            }
        }
        
        if (is_prime) {
            arr[i] = arr[i] * arr[i];
        }
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}