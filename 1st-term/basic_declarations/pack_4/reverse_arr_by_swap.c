// Write a C program to read an array of length 6, change the first element by the last, 
// the second element by the fifth and the third element by the fourth. 
// Print the elements of the modified array. 

#include <stdio.h>
int main() {
    int n = 6;
    int arr[n];
    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }
    for (int i = 0; i < (n / 2); ++i) {
        int temp = arr[i];
        arr[i] = arr[n - i - 1];
        arr[n - i - 1] = temp;
    }
    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
}