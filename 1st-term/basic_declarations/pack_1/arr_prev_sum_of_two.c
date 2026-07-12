// Write a C program to populate an array where each element is the sum of the two preceding elements.
#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    int arr[n];

    // задаём первые два элемента
    arr[0] = 1;
    arr[1] = 1;

    // заполняем остальные элементы
    for (int i = 2; i < n; i++) {
        arr[i] = arr[i - 1] + arr[i - 2];
    }

    // вывод массива
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}