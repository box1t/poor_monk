// Write a C program to find the largest value from the first, last, and middle elements of a given array of integers of odd length (at least 1). 

int largest_val(int n1, int n2, int n3) {

    if (n1 > n2) {
        int temp = n1; n1 = n2; n2 = temp;
    }
    if (n2 > n3) {
        int temp = n2; n2 = n3; n3 = temp;
    }
    if (n1 > n2) {
        int temp = n1; n1 = n2; n2 = temp;
    }
    return n3;
}

#include <stdio.h>

int main() {
    int arr[] = {14, 2, 3, 1, 18, 1, 1, 1, 15};
    int arr_sz = sizeof(arr) / sizeof(arr[0]);

    int first = arr[0];
    int last = arr[arr_sz - 1];
    int mid = arr[arr_sz / 2];
    printf("%d", largest_val(first, last, mid));

}