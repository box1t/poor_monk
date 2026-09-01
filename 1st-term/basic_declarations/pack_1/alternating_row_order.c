// Write a C program to display a p x q grid with alternating row orders (one row ascending, the next descending).

#include <stdio.h>

int main() {
    int p, q; // p - строки, q - столбцы
    scanf("%d %d", &p, &q);

    int number = 1;

    for (int i = 0; i < p; i++) { // Какую по счету строку создаем и выводим?

        int row[q]; // длина одной строки - q
        // длина строки равна количеству столбцов, потому что именно столбцы и задают ширину таблицы.
        
        // Заполняем строку
        for (int j = 0; j < q; j++) {
            row[j] = number;
            number++;
        }

        // Нечётные строки (0,2,4...) — слева направо
        if (i % 2 == 0) {
            for (int j = 0; j < q; j++) {
                printf("%d ", row[j]);
            }
        }
        // Чётные строки (1,3,5...) — справа налево
        else {
            for (int j = q - 1; j >= 0; j--) {
                printf("%d ", row[j]);
            }
        }

        printf("\n");
    }

    return 0;
}