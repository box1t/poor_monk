/*
Write a program in C to count the total number of duplicate elements in an array. 
*/

#include <stdio.h>
int main() {
    int i, j, n , arr[n], ctr = 0;
    scanf("%d", &n);
    for (i = 0; i < 10; ++i) {
        printf("element - %d : ", i);
        scanf("%d", &arr[i]);
    }

    for (i = 0; i < n; ++i) {
        for (j = i + 1; j <n; ++j) {
            if (arr[i] == arr[j]) {
                ctr++;
                break;
            }
        }
    }
    return 0;

}
