// "встречается ли число подряд трижды в массиве"

#include <stdio.h>

int main() {
    int arr[] = {1, 2, 3, 3, 3};
    int num = 3;
    int sz = sizeof(arr) / sizeof(arr[0]);
    int flag = 0;
    for (int i = 2; i < sz; ++i) {
        if (arr[i - 2] == arr[i - 1] == arr[i] == num) {
            printf("appears");
            flag = 1;
            break;
        }
    }
    if (!flag) {
        printf("does not appear");
    }
}