// Write a C program to segregate an array into three parts: even, odd, and zeros in the middle.

void segregate_stable(int arr[], int new_arr[], int sz) {
    int idx = 0;
    
    // 1. Сначала копируем все ненулевые четные
    for (int i = 0; i < sz; ++i) {
        if (arr[i] % 2 == 0 && arr[i] != 0) {
            new_arr[idx++] = arr[i];
        }
    }
    
    // 2. Затем копируем все нули
    for (int i = 0; i < sz; ++i) {
        if (arr[i] == 0) {
            new_arr[idx++] = arr[i];
        }
    }
    
    // 3. В конце копируем все нечетные
    for (int i = 0; i < sz; ++i) {
        if (arr[i] % 2 != 0) {
            new_arr[idx++] = arr[i];
        }
    }
}