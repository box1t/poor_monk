// Write a C program to create an array after replacing all the values 5 with 0 and shifting all zeros to the right. 

#include <stdio.h>

void replace_and_shift(int arr[], int arr_sz) {
    int write_pos = 0; // Указатель, куда записывать следующее "хорошее" число

    // ШАГ 1: Проходим по массиву и сохраняем только те числа, 
    // которые НЕ равны 0 и НЕ равны 5.
    for (int i = 0; i < arr_sz; ++i) {
        if (arr[i] != 0 && arr[i] != 5) {
            arr[write_pos] = arr[i];
            write_pos++;
        }
        // Если число равно 5 или 0, мы его просто игнорируем (не записываем в write_pos)
    }

    // ШАГ 2: Все элементы от write_pos до конца массива должны быть нулями.
    // Это автоматически обрабатывает и исходные нули, и пятерки, которые стали нулями.
    while (write_pos < arr_sz) {
        arr[write_pos] = 0;
        write_pos++;
    }
}

int main() {
    int arr[] = {2, 2, 2, 8, 10, 5, 5, 0, 15};
    int arr_sz = sizeof(arr) / sizeof(arr[0]);
    
    // Убрали лишний new_arr, так как модифицируем массив на месте (in-place)
    replace_and_shift(arr, arr_sz);
    
    for (int i = 0; i < arr_sz; ++i) {
        printf("%d ", arr[i]);
    }
    // Ожидаемый вывод: [ 2 2 2 8 10 15 0 0 0 ]
    
    return 0;
}

/*

#include <stdio.h>

int main() {
    int a[100], n;
    int j = 0;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    printf("Enter the array elements:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    // Replace all 5s with 0s
    for (int i = 0; i < n; i++) {
        if (a[i] == 5) {
            a[i] = 0;
        }
    }

    // Shift all zeros to the right
    for (int i = 0; i < n; i++) {
        if (a[i] != 0) {
            a[j] = a[i];
            j++;
        }
    }

    // Fill the remaining positions with zeros
    while (j < n) {
        a[j] = 0;
        j++;
    }

    printf("Modified array:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }

    return 0;
}

*/