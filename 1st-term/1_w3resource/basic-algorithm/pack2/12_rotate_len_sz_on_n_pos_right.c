// Write a C program to rotate the elements of a given array of integers (length sz) in the right direction (on N positions) and return the updated array. 


void reverse(int arr[], int start, int end) {
    while (start < end) {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

void rotate_arr(int arr[], int sz, int n) {
    if (sz <= 1) {
        return;
    }
    n = n % sz;

    // Алгоритм трёх обращений для сдвига ВПРАВО:
    
    // Шаг А: Переворачиваем ВЕСЬ массив целиком
    reverse(arr, 0, sz - 1);
    
    // Шаг Б: Переворачиваем первые n элементов (они встанут в правильный порядок)
    reverse(arr, 0, n - 1);
    
    // Шаг В: Переворачиваем оставшуюся часть массива (они тоже встанут в правильный порядок)
    reverse(arr, n, sz - 1);

}
