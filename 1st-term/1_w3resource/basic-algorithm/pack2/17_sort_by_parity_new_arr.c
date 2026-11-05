// Write a C program to sort an array by parity: placing even numbers in ascending order followed by odd numbers in descending order.
// с дополнительным массивом

#include <stdio.h>

void bubble_sort_asc(int arr[], int arr_sz) {
    for (int i = 0; i < arr_sz - 1; ++i) {
        for (int j = 0; j < arr_sz - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void bubble_sort_desc(int arr[], int arr_sz) {
    for (int i = 0; i < arr_sz - 1; ++i) {
        for (int j = 0; j < arr_sz - i - 1; ++j) {
            if (arr[j] < arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void sort_by_parity(int arr[], int new_arr[], int arr_sz) {
    int count_even = 0;
    int count_odd = 0;
    
    for (int i = 0; i < arr_sz; ++i) {
        if (arr[i] % 2 == 0) {
            new_arr[count_even] = arr[i];
            count_even++;
        }
    }
    bubble_sort_asc(new_arr, count_even);

    for (int j = arr_sz - 1; j >= 0; --j) {
        if (arr[j] % 2 != 0) {
            new_arr[count_even + count_odd] = arr[j];
            count_odd++;
        }
    }
    bubble_sort_desc(new_arr + count_even, count_odd);
}

int main() {
    int arr[] = {2, 2, 2, 8, 10, 12, 5, 0, 15};
    int arr_sz = sizeof(arr) / sizeof(arr[0]);
    int new_arr[arr_sz];
    sort_by_parity(arr, new_arr, arr_sz);
    for (int i = 0; i < arr_sz; ++i) {
        printf("%d ", new_arr[i]);
    }
}

// без дополнительного массива

/*
#include <stdio.h>

void sort_by_parity(int arr[], int arr_sz) {
    int left = 0;
    int right = arr_sz - 1;

    // Работаем, пока указатели не встретились или не пересеклись
    while (left < right) {
        
        // 1. Двигаем left вправо, пока он указывает на ЧЕТНОЕ число
        // (Условие left < right обязательно, чтобы не выйти за границы)
        while (left < right && arr[left] % 2 == 0) {
            left++;
        }

        // 2. Двигаем right влево, пока он указывает на НЕЧЕТНОЕ число
        while (left < right && arr[right] % 2 != 0) {
            right--;
        }

        // 3. Если указатели не пересеклись, значит мы нашли:
        //    - слева нечетное (которое должно быть справа)
        //    - справа четное (которое должно быть слева)
        //    Меняем их местами!
        if (left < right) {
            int temp = arr[left];
            arr[left] = arr[right];
            arr[right] = temp;
            
            // После обмена можно сразу сдвинуть оба указателя
            left++;
            right--;
        }
    }
}

int main() {
    int arr[] = {0, 0, 1, 2, 3, 0, 4, 0, 5, 0};
    int arr_sz = sizeof(arr) / sizeof(arr[0]);

    sort_by_parity(arr, arr_sz);

    for (int i = 0; i < arr_sz; ++i) {
        printf("%d ", arr[i]);
    }
    // Ожидаемый вывод: 0 0 0 0 0 2 4 3 1 5 
    // (Все четные слева, все нечетные справа. 
    // Порядок внутри групп не гарантируется, но это и не требуется)
    
    return 0;
}
*/