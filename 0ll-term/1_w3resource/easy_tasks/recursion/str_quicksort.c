// Write a C program to sort the characters of a string in descending order using quicksort.

#include <stdio.h>
#include <string.h>

// Функция для обмена двух символов
void swap(char* a, char* b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

// Функция разбиения (Partition) для быстрой сортировки
int partition(char arr[], int low, int high) {
    // Выбираем последний элемент как опорный (pivot)
    char pivot = arr[high]; 
    
    // Индекс меньшего (в данном случае - большего, т.к. сортируем по убыванию) элемента
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        // КЛЮЧЕВОЕ ИЗМЕНЕНИЕ ДЛЯ УБЫВАНИЯ:
        // Если текущий элемент БОЛЬШЕ опорного, мы перемещаем его влево
        if (arr[j] > pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    
    // Помещаем опорный элемент на его правильную отсортированную позицию
    swap(&arr[i + 1], &arr[high]);
    
    // Возвращаем индекс опорного элемента
    return (i + 1);
}

// Основная рекурсивная функция быстрой сортировки
void quicksort(char arr[], int low, int high) {
    if (low < high) {
        // pi - индекс разбиения, arr[pi] теперь на своем месте
        int pi = partition(arr, low, high);

        // Рекурсивно сортируем элементы до и после разбиения
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

int main() {
    char str[] = "kraboed"; // Пример строки
    
    // ВАЖНО: Используем strlen, чтобы получить длину БЕЗ учета '\0'.
    // Если отсортировать '\0' (код 0) по убыванию, он окажется в начале строки, 
    // и printf сразу же завершит вывод, показав пустую строку.
    int n = strlen(str);

    printf("Original string: %s\n", str);

    // Запускаем сортировку от индекса 0 до n-1
    quicksort(str, 0, n - 1);

    printf("Sorted string (descending): %s\n", str);

    return 0;
}