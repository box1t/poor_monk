// Write a C program to check whether the sequence of numbers 1, 2, 3 appears in a given array of integers somewhere. 
#include <stdio.h>

int main() {

    int arr[10] = {1, 2, 3, 1, 2, 3};
    int sz = sizeof(arr) / sizeof(arr[0]);
    int flag = 0;

    if (sz >= 3) {
        for (int i = 2; i < sz; ++i) {
            if (arr[i] == 3 && arr[i - 1] == 2 && arr[i - 2] == 1) {
                printf("appears\n");
                flag = 1;
                break;
            }
        }
    }
    if (!flag) {
        printf("does not appear");
    }
}