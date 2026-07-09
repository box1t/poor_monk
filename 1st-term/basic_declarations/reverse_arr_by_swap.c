// Write a C program to read an array of length 6, change the first element by the last, 
// the second element by the fifth and the third element by the fourth. 
// Print the elements of the modified array. 

#include <stdio.h>
int main() {
    int arr[6];
    for (int i = 0; i < 6; ++i) {
        scanf("%d", &arr[i]);
    }
    for (int i = 0; i < 3; ++i) {
        int temp = arr[6 - i - 1];
        arr[6 - i - 1] = arr[i];
        arr[i] = temp;
    }
    for (int i = 0; i < 6; ++i) {
        printf("%d ", arr[i]);
    }
}