// Write a C program to reverse segments of an array of user-defined size using in-place swaps.
#include <stdio.h>

int main() {
    int n, size;

    scanf("%d", &n);

    int arr[n];

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    scanf("%d", &size);

    // выполняем обработку, пока начало сегмента находится внутри массива
    for (int start = 0; start < n; start += size) {

        // // Левая граница сегмента — это его начало
        int left = start;
        int right = start + size - 1;

        // если последний сегмент меньше size
        if (right >= n) {
            right = n - 1; // Обрезаем правую границу до реального конца массива
        }

        // разворот сегмента
        while (left < right) {

            int temp = arr[left];
            arr[left] = arr[right];
            arr[right] = temp;

            left++;
            right--;
        }
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}