// Написать на Си табуляцию многочлена и его производной на отрезке (схема Горнера)

#include <stdio.h>

// Функция вычисления значения многочлена по схеме Горнера
// coeffs: массив коэффициентов, где coeffs[0] - это a_0 (свободный член),
// coeffs[degree] - это a_n (старший коэффициент).
// degree: степень многочлена (длина массива - 1)
double eval_poly(const double coeffs[], int degree, double x) {
    double result = coeffs[degree];
    for (int i = degree - 1; i >= 0; i--) {
        result = result * x + coeffs[i];
    }
    return result;
}

// Функция для получения коэффициентов производной
// Производная от a_n * x^n равна (n * a_n) * x^(n-1)
void get_derivative(const double coeffs[], int degree, double deriv_coeffs[]) {
    for (int i = 0; i < degree; i++) {
        deriv_coeffs[i] = (i + 1) * coeffs[i + 1];
    }
}

int main() {
    // Пример: P(x) = 2x^3 - 3x^2 - 12x + 5
    // Коэффициенты записываем от младшей степени к старшей: a_0, a_1, a_2, a_3
    double coeffs[] = {5.0, -12.0, -3.0, 2.0};
    
    // Автоматический расчет степени многочлена
    int degree = (sizeof(coeffs) / sizeof(coeffs[0])) - 1;
    
    // Массив для коэффициентов производной (его степень на 1 меньше)
    double deriv_coeffs[degree];
    get_derivative(coeffs, degree, deriv_coeffs);

    // Параметры табуляции (отрезок [a, b] и шаг)
    double start = -2.0;
    double end = 3.0;
    double step = 0.5;

    // Вывод заголовка таблицы
    printf("Табуляция функции P(x) = 2x^3 - 3x^2 - 12x + 5\n");
    printf("и её производной P'(x) = 6x^2 - 6x - 12\n");
    printf("------------------------------------------------------------\n");
    printf("|   x    |     P(x)      |     P'(x)     |  Экстремум?  |\n");
    printf("------------------------------------------------------------\n");

    // Цикл табуляции
    // ВАЖНО: x <= end + 1e-9 защищает от проблем с точностью чисел с плавающей точкой
    for (double x = start; x <= end + 1e-9; x += step) {
        
        // Вычисляем значения
        double px = eval_poly(coeffs, degree, x);
        double dpx = eval_poly(deriv_coeffs, degree - 1, x);
        
        // Простая проверка на экстремум (если производная близка к 0)
        const char* extremum = (dpx > -0.01 && dpx < 0.01) ? "  <--" : "";

        // Красивый форматированный вывод
        printf("| %6.2f | %13.6f | %13.6f |%12s |\n", x, px, dpx, extremum);
    }
    
    printf("------------------------------------------------------------\n");

    return 0;
}