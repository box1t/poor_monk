
/*
Write a C program that reads an array (length 10), 
and replaces the first element of the array by a given number 
and replaces each subsequent position of the array by one-third the value of the previous.
*/


/*
1. Читаем массив (первый цикл)
2. Вводим число и заменяем arr[0]
3. Заполняем оставшиеся элементы по формуле (второй цикл)
4. Выводим массив, не забываем про форматирование
*/


#include <stdio.h>

int main() {
    int arr_size = 10;
    double arr[arr_size];

    for (int i = 0; i < arr_size; ++i) {
        scanf("%lf", &arr[i]); 
        // scanf("%0.2lf", &arr[i]); - так некорректно! 

    }

    double input_num;
    printf("Введите число: ");
    scanf("%lf", &input_num);
    arr[0] = input_num;

    double temp = arr[0];  
    for (int i = 1; i < arr_size; ++i) {
        temp *= 0.33;
        arr[i] = (double)temp;  
    }

    for (int i = 0; i < arr_size; ++i) {
        printf("%0.3lf", arr[i]);
        if (i != arr_size - 1) {
            printf(", ");
        }   // Запятая, если это не последний элемент
        if ((i + 1) % 5 == 0) {
            printf("\n");
        }  // Перенос строки каждые 5 элементов
    }
    printf("\n\n");  
}
