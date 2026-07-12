// Write a C program that read 5 numbers and sum of all odd values between them. 
#include <stdio.h>

int main() {
    int arr[5];

    for (int i = 0; i < 5; i++) {
        scanf("%d", &arr[i]);
    }

    int sum_odds = 0;

    for (int i = 0; i < 4; i++) {
        int left = arr[i];
        int right = arr[i + 1];

        if (left > right) {
            int temp = left;
            left = right;
            right = temp;
        }

        for (int x = left + 1; x < right; x++) {
            if (x % 2 != 0) {
                sum_odds += x;
            }
        }
    }

    printf("%d", sum_odds);

    return 0;
}