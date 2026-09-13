
// Напишите свой бенчмарк на Си 
// для сравнения возведения в степень двойки и битового сдвига

/*
#include <stdio.h>
#include <math.h>
#include <time.h>

#define ITERATIONS 10000000

int main() {
    clock_t start, end;
    int result;

    // Тест битового сдвига
    start = clock();
    for (int i = 0; i < ITERATIONS; ++i) {
        result = 1 << (i % 31);  // Ограничение, чтобы избежать переполнения
    }
    end = clock();
    double shift_time = (double)(end - start) / CLOCKS_PER_SEC;

    // Тест pow(2, i)
    start = clock();
    for (int i = 0; i < ITERATIONS; ++i) {
        result = (int)pow(2, i % 31);
    }
    end = clock();
    double pow_time = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Bit shift time: %f seconds\n", shift_time);
    printf("pow(2, i) time: %f seconds\n", pow_time);

    return 0;
}

*/