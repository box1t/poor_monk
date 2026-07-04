/*
Write a program in C to find the sum of all elements of the array.
Test Data :
Input the number of elements to be stored in the array :3
Input 3 elements in the array : 
*/

#include <stdio.h>
int main() {
    int i, n, arr[10];
    int summa = 0;
    scanf("%d", &n);
    for (i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
        summa += arr[i];
    }
    printf("%d", summa);
}