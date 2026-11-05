
// Напишите на языке Си функцию возведения в степени для использования в задаче print_pow

/*

#include <stdio.h>

// Функция быстрого возведения в степень (целочисленное)
long long int power(int base, int exp) {
    long long int result = 1;
    while (exp > 0) {
        if (exp % 2 == 1)  // Если степень нечётная
            result *= base;
        base *= base; // Квадрат базы
        exp /= 2;
    }
    return result;
}

int main() {
    int base = 3; // Теперь можно задать любое число вместо 2
    printf("=======================================================\n");
    printf("iteration | %d^i             | %d^-i\n", base, base);
    printf("=======================================================\n");

    for (size_t i = 0; i <= 10; ++i) {
        printf("%-9zu | %-16lld | %.12f\n", i, power(base, i), 1.0 / power(base, i));
    }

    printf("=======================================================\n");
    return 0;
}

*/