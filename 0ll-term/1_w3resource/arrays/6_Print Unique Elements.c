/*
Write a program in C to print all unique elements in an array.

This task requires writing a C program to identify and print all unique elements 
in an array. The program will accept a specified 
number of integer inputs, store them in an array, 
and then determine and display the elements that appear only once in the array

*/

#include <stdio.h>

int main() {
    int i, j, n, ctr = 0;
    scanf("%d", &n);

    int arr[n];
    for (i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }
    for (i = 0; i < n; ++i) {
        ctr = 0;
        for (j = 0; j < n; ++j) {
            if (i != j) {
                if (arr[i] == arr[j]) {
                    ctr++;
                }
            }
        }
        if (ctr == 0) {
            printf("%d", arr[i]);
        }
    }

    return 0;
}
