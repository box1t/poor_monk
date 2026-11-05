// "общее количество совпадений числа во всём массиве"

#include <stdio.h>

int main() {
    int arr[] = {1, 2, 3, 3};
    int num = 3;
    int count = 0;
    int sz = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < sz; ++i) {
        if (arr[i] == num) {
            count++;
        }
    }
    printf("[%d] - number of matching");
}