// Write a C program that reads a sequence of integers and finds the element that occurs most frequently.

#include <stdio.h>

int main() {

    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int most = arr[0];
    int maxCount = 1;

    // Проверяем каждый элемент
    for (int i = 0; i < n; i++) {

        int count = 0;

        // Считаем, сколько раз он встречается
        for (int j = 0; j < n; j++) {

            if (arr[i] == arr[j]) {
                count++;
            }
        }

        // Если нашли более частый элемент
        if (count > maxCount) {
            maxCount = count;
            most = arr[i];
        }
    }

    printf("Most frequent element: %d\n", most);
    printf("Occurrences: %d\n", maxCount);

    return 0;
}