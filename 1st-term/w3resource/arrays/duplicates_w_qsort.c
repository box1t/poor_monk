
/*
Count the total number of duplicate elements in an array 
*/


#include <stdio.h>
#include <stdlib.h>

int comparator(const void* a, const void* b) {
    return (*(int*)(a) - *(int*)(b));
}

void find_duplicates(int arr[], int arr_size) {
    if (arr_size == 0) {
        return;
    }
    qsort(arr, arr_size, sizeof(int), comparator); 

    int i = 0;
    while(i < arr_size - 1) {
        if (arr[i] == arr[i + 1]) {
            printf("%d", arr[i]); // start of duplicates
            
            while(i < arr_size - 1 && arr[i] == arr[i + 1]) {
                ++i;
            }
        }
        ++i;
    }
}

/*

void count_duplicates(int arr[], int n) {
    if (n == 0) {
        return;
    }

    qsort(arr, n, sizeof(int), compare);
    int max_value = arr[n - 1];
    int* count = (int*)calloc(max_value + 1, sizeof(int)); // Массив частот

    for (int i = 0; i < n; ++i) {
        ++count[arr[i]];
    }
    for (int i = 0; i <= max_value; ++i) {
        if (count[i] > 1) {
            printf("%d встречается %d раз(а)\n", i, count[i]);
        }
    }
    free(count);
}

*/

int main() {
    const int arr_size = 10;
    int arr[arr_size] = {1, 1, 2, 2, 2, 3, 4, 5, 5, 5};

    find_duplicates(arr, arr_size);
}

