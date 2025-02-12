
/*
Write a program in C to find the sum of the series [1-X^2/2!+X^4/4!].
*/

#include <stdio.h>
#include <math.h>

int factorial(int number) {
    int result = 1;
    if (number == 0) {
        return 1;
    }  
    for (int i = 1; i <= number; ++i) {
        result *= i;
    }
    return result;
}

int main() {
    int series_lim = 5;
    int x = 2;
    double sum_of_series = 0.0;
    for (int i = 0; i < series_lim; ++i) {
        double current_series_value = pow(-1, i) * pow(x, 2 * i) / factorial(2 * i);
        sum_of_series += current_series_value;
        printf("%lf", current_series_value);

        if (i != series_lim - 1) {
            printf(", ");
        } 
        if ((i + 1) % 5 == 0) {
            printf("\n");
        }
    }
    printf("Сумма ряда: %lf", sum_of_series);
    printf("\n\n");
}