// Write a C program to reverse segments of an array of user-defined size using in-place swaps.
#include <stdio.h>

int main() {
    int n, size;

    scanf("%d", &n);

    int arr[n];

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    scanf("%d", &size);

    // выполняем обработку, пока начало сегмента находится внутри массива
    for (int start = 0; start < n; start += size) {

        int left = start; // индекс левого края сегмента (его начало).
        int right = start + size - 1; // индекс правого края сегмента (его конец).

        // не вылезли ли за реальный конец массива
        if (right >= n) {
            right = n - 1; // Обрезаем правую границу до реального конца массива
        }

        // разворот сегмента
        // Повторять обмен элементов до тех пор, пока указатели не встретятся или не пересекутся
        // знак <, чтобы не менять центральный элемент с самим собой при нечетной длине сегмента, указатели встретятся на нем
        while (left < right) {

            int temp = arr[left]; // Шаг 1: Сохраняем левое значение
            arr[left] = arr[right]; // Шаг 2: Перезаписываем левое правым
            arr[right] = temp; // Шаг 3: Перезаписываем правое сохраненным левым

            left++;
            right--;
        }
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}