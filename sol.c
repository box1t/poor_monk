// Write a C program to reverse segments of an array of user-defined size using in-place swaps.

#include <stdio.h>

int main() {
    int n, size;
    scanf("%d %d", &n, &size);
    int arr[n];
    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }

    for (int start = 0; start < n; start += size) {
        int left = start;
        int right = start + size - 1;

        while (left < right) {
            int temp = left;
            left = right;
            right = temp;

            ++left;
            --right;
        }
    }
}