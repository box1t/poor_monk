
#include <stdio.h>
#include <stdlib.h> 



void bubble_sort(float *arr, int n) {
    if (arr == NULL || n <= 1) {
        return;
    }
    int i, j;
    for (i = 0; i < n - 1; ++i) {
        for (j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                float temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n; 
    scanf("%d", &n);

    float *arr;
    arr = (float*) malloc(n * sizeof(float));

    for (int i = 0; i < n; ++i) {
        scanf("%f", &arr[i]);
    }

    bubble_sort(arr, n);
    for (int i = 0; i < n; ++i) {
        printf("%0.6e ", arr[i]);
    }

    free(arr);
    arr = NULL;

    return 0;
}