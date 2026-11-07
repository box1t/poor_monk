// Write a C program that reads a sequence of integers and finds the element that occurs most frequently.

#include <stdio.h>

int main() {

    int arr[10];
    for (int i = 0; i < 10; ++i) {
        scanf("%d", &arr[i]);
    } 
    int most_frequent_val = arr[0];
    
    int frequencies[10];
    for (int i = 0; i < 10; ++i) {
        frequencies[i] = 0;
    } 
    int highest_frequency = frequencies[0];

    int count = 0;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (arr[i] == arr[j]) {
                count++;
                frequencies[i] = count;
            }
        }
        count = 0;
    }

    for (int i = 0; i < 10; ++i) {
        if (frequencies[i] > highest_frequency) {
            highest_frequency = frequencies[i];
            most_frequent_val = arr[i];

        }
    }
    for (int i = 0; i<10; ++i) {
        printf("[%d]-value [%d]-frequency\n", arr[i], frequencies[i]);
    }
}


/*
#include <stdio.h>

int main() {

    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int most = arr[0];
    int maxCount = 0;

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
*/