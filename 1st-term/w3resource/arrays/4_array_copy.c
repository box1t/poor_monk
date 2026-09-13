/*
Write a program in C to copy the elements of one array into another array.

The task involves writing a C program to copy the elements from one array to another. 
The program will take a specified number of integer inputs to store in the first array, 
then copy these elements to a second array, 
and finally display the contents of both arrays.
*/

#include <stdio.h>
int main() {
    int i, n, arr1[n], arr2[n];
    scanf("%d", &n);
    for (i = 0; i < n; ++i) {
        scanf("%d", &arr1[i]);
    }
    for (i = 0; i < n; ++i) {
        arr2[i] = arr1[i];
    }
    for (i = 0; i < n; ++i) {
        printf("%d", arr2[i]);
    }
}
