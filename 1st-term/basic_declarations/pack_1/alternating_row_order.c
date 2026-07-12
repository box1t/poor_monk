// Write a C program to display a p x q grid with alternating row orders (one row ascending, the next descending).

#include <stdio.h>

int main() {
    int p, q;
    scanf("%d %d", &p, &q);

    int number = 1;

    for (int i = 0; i < p; i++) {

        int row[q];

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