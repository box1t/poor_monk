
/*
Write a program in C to display the n terms of a harmonic series and their sum.
*/

/*
1. Формула гармонического ряда:
1 / i
Заведем цикл, заведем временную переменную для отображения текущего значения, а также для суммы.

*/

#include <stdio.h>

int main() {
    double current_value = 0;
    int series_limiter = 5;
    double sum = 0;
    for (int i = 1; i <= series_limiter; ++i) {
        current_value = 1 / (double)i;
        sum += current_value;
        printf("%lf", current_value);
        
        if (i != series_limiter) {
            printf(", ");
        } 
        if (i % 5 == 0 && i != series_limiter) {
            printf("\n");
        }
    }
    printf("\n");
    printf("Sum series: %lf\n\n", sum);
}