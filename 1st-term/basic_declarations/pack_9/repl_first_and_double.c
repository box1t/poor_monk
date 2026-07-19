// Write a C program that reads an array of integers (length 7), and replaces the first element of the array 
// by a given number and replaces each subsequent position of the array by the double value of the previous.

#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }
    int number;
    scanf("%d", &number);
    
    arr[0] = number;
    for (int i = 1; i <= n; ++i) {
        arr[i] = arr[i - 1] * 2;
        printf("%d ", arr[i - 1]);
    }

}