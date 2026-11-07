// - дифференцирование многочлена Си

#include <stdio.h>

// Функция вычисления коэффициентов производной
// Заполняет массив deriv_coeffs на основе исходных coeffs
void differentiate(const double coeffs[], int degree, double deriv_coeffs[]) {
    for (int i = 0; i < degree; i++) {
        deriv_coeffs[i] = (i + 1) * coeffs[i + 1];
    }
}

// Функция красивого вывода многочлена
void print_polynomial(const double coeffs[], int degree, const char *name) {
    printf("%s(x) = ", name);
    
    int first_term = 1; // Флаг для обработки знака первого члена
    
    // Идем от старшей степени к младшей
    for (int i = degree; i >= 0; i--) {
        double coeff = coeffs[i];
        
        if (coeff == 0.0) continue; // Пропускаем нулевые члены
        
        // Обработка знака
        if (coeff > 0 && !first_term) {
            printf("+ ");
        } else if (coeff < 0) {
            printf("- ");
            coeff = -coeff;
        }
        
        // Вывод коэффициента (если не 1, либо это свободный член)
        if (i == 0 || coeff != 1.0) {
            printf("%.0f", coeff);
        }
        
        // Вывод переменной x и степени
        if (i > 0) {
            printf("x");
            if (i > 1) {
                printf("^%d", i);
            }
            printf(" ");
        }
        
        first_term = 0;
    }
    
    if (first_term) {
        printf("0"); // Если все коэффициенты были нулевыми
    }
    
    printf("\n");
}

int main() {
    // P(x) = 2x^3 - 3x^2 - 12x + 5
    // Коэффициенты от младшей степени к старшей: a_0, a_1, a_2, a_3
    double coeffs[] = {5.0, -12.0, -3.0, 2.0};
    int degree = (sizeof(coeffs) / sizeof(coeffs[0])) - 1;
    
    // Массив для производной (его размер на 1 меньше)
    double deriv_coeffs[degree];
    
    // Дифференцируем
    differentiate(coeffs, degree, deriv_coeffs);
    
    // Выводим результат
    printf("=== Дифференцирование многочлена ===\n\n");
    print_polynomial(coeffs, degree, "P");
    print_polynomial(deriv_coeffs, degree - 1, "P'");
    
    return 0;
}