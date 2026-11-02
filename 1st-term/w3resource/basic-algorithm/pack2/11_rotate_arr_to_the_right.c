// Write a C program to rotate the elements of an array to the right by one position.

void rotate_arr(int arr[], int sz) {
    if (sz <= 1) {
        return;
    }
    int temp = arr[sz - 1];
    for (int i = sz - 1; i > 0; --i) { // При сдвиге вправо мы читаем из i-1 (слева), поэтому идем справа налево, чтобы не затереть левые данные раньше времени.
        arr[i] = arr[i-1];
    }
    arr[0] = temp;
}
