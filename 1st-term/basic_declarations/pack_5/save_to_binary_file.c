// Write a C program to generate 50 random numbers in a given range,
// sort them, and then write them to a binary file and then read them

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 50

int main() {

    double arr[SIZE];
    double min, max;
    FILE *fptr;

    printf("Enter range (min max): ");
    scanf("%lf %lf", &min, &max);

    srand(time(NULL));


    // Генерация 50 случайных чисел в диапазоне min - max
    for (int i = 0; i < SIZE; i++) {
        arr[i] = min + ((double)rand() / RAND_MAX) * (max - min);
    }


    // Сортировка массива (Bubble Sort)
    for (int i = 0; i < SIZE - 1; i++) {

        for (int j = 0; j < SIZE - 1 - i; j++) {

            if (arr[j] > arr[j + 1]) {

                double temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;

            }
        }
    }


    // Запись в бинарный файл
    fptr = fopen("numbers.dat", "wb");

    if (fptr == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    fwrite(arr, sizeof(arr[0]), SIZE, fptr);

    fclose(fptr);


    // Чтение из бинарного файла
    fptr = fopen("numbers.dat", "rb");

    if (fptr == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    double read_arr[SIZE];

    fread(read_arr, sizeof(read_arr[0]), SIZE, fptr);

    fclose(fptr);


    // Вывод прочитанных чисел
    printf("Sorted numbers:\n");

    for (int i = 0; i < SIZE; i++) {

        printf("%.4lf ", read_arr[i]);

        if ((i + 1) % 10 == 0) {
            printf("\n");
        }
    }


    return 0;
}