// Write a C program to create an array of length n and fill the array elements with integer values. Find the smallest value and its position in the array.

#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }
    int min = arr[0];
    int position = 0;
    for (int i = 1; i < n; ++i) {
        if (arr[i] < min) {
            min = arr[i];
            position = i;
        }
    }
    printf("position: [%d] \nmin value [%d]", position, min);
}