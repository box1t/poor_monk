#include <stdio.h>

int main() {
    int numbers[6]; 
    int input_number;

    for (int i = 0; i < 6; ++i) {
        scanf("%d", &input_number);
        numbers[i] = input_number; 
    }

    int smallest_index = 0; 
    for (int i = 1; i < 6; ++i) { 
        if (numbers[i] < numbers[smallest_index]) {
            smallest_index = i; 
        }
    }

    printf("Smallest element: %d, Index: %d\n", numbers[smallest_index], smallest_index);
    return 0; 
}