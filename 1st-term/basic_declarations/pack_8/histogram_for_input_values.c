// Write a C program that takes some integer values from the user and prints a histogram.
#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }

    for (int i = 0; i < n; ++i) {
        printf("%d:", arr[i]);
        for (int j = 0; j < arr[i]; ++j) {
            printf("*");
        }
        printf("\n");
    }
}