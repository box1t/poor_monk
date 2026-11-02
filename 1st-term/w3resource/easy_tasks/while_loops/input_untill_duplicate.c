// Write a C program that prompts the user to input a series of numbers until they input a duplicate number. Use a while loop to check for duplicates. 

#include <stdio.h>

int main() {
    int n = 10;
    int arr[n];
    int duplicate = 0;
    int i = 0;

    printf("Введите числа (максимум %d). Повтор остановит программу.\n", n);

    while (!duplicate && i < n) {        
        scanf("%d", &arr[i]);
        
        for (int j = 0; j < i; ++j) {
            if (arr[i] == arr[j]) {
                duplicate = 1;
                printf("Найден дубликат: %d\n", arr[i]);
                break; 
            }
        }
        
        if (!duplicate) {
            ++i;
        }
    }

    if (!duplicate) {
        printf("Дубликат не найден среди %d введенных чисел.\n", i);
    }

    return 0;
}