// Write a C program to check whether the sequence of numbers 1, 2, 3 appears in a given array of integers somewhere. 

#include <stdio.h>

int main() {
    int arr[] = {1, 2, 2, 1, 2, 3};
    int arr_sz = sizeof(arr) / sizeof(arr[0]);
    int pattern[] = {1, 2, 3};
    int pattern_sz = sizeof(pattern) / sizeof(pattern[0]);
    int flag = 0;
    
    // Проходим по всем возможным начальным позициям
    for (int i = 0; i <= arr_sz - pattern_sz; ++i) {
        int match = 1;
        
        // Проверяем, совпадает ли подпоследовательность с шаблоном
        for (int j = 0; j < pattern_sz; ++j) {
            if (arr[i + j] != pattern[j]) {
                match = 0;
                break;
            }
        }
        
        if (match) {
            printf("appears\n");
            flag = 1;
            break;
        }
    }
    
    if (!flag) {
        printf("does not appear\n");
    }
    
    return 0;
}