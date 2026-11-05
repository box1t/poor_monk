// - перемножение многочленов на си

#include <stdio.h>

// Функция умножения двух многочленов
// coeffs1 (degree1) * coeffs2 (degree2) -> result (degree1 + degree2)
void multiply_polynomials(const double coeffs1[], int degree1,
                          const double coeffs2[], int degree2,
                          double result[]) {
    int result_degree = degree1 + degree2;
    
    // 1. Обнуляем массив результата
    for (int i = 0; i <= result_degree; i++) {
        result[i] = 0.0;
    }
    
    // 2. Два вложенных цикла: перебираем все пары коэффициентов
    for (int i = 0; i <= degree1; i++) {
        for (int j = 0; j <= degree2; j++) {
            // При умноении x^i на x^j получаем x^(i+j)
            result[i + j] += coeffs1[i] * coeffs2[j];
        }
    }
}

// Функция красивого вывода многочлена (из предыдущего ответа)
void print_polynomial(const double coeffs[], int degree, const char *name) {
    printf("%s(x) = ", name);
    
    int first_term = 1;
    
    for (int i = degree; i >= 0; i--) {
        double coeff = coeffs[i];
        
        if (coeff == 0.0) continue;
        
        if (coeff > 0 && !first_term) {
            printf("+ ");
        } else if (coeff < 0) {
            printf("- ");
            coeff = -coeff;
        }
        
        if (i == 0 || coeff != 1.0) {
            printf("%.0f", coeff);
        }
        
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
        printf("0");
    }
    
    printf("\n");
}

int main() {
    // Пример: (2x^2 + 3x + 1) * (x + 2)
    // Коэффициенты от младшей степени к старшей
    
    // P(x) = 2x^2 + 3x + 1
    double coeffs1[] = {1.0, 3.0, 2.0};
    int degree1 = (sizeof(coeffs1) / sizeof(coeffs1[0])) - 1;
    
    // Q(x) = x + 2
    double coeffs2[] = {2.0, 1.0};
    int degree2 = (sizeof(coeffs2) / sizeof(coeffs2[0])) - 1;
    
    // Результат будет степени degree1 + degree2
    int result_degree = degree1 + degree2;
    double result[result_degree + 1];
    
    // Умножаем
    multiply_polynomials(coeffs1, degree1, coeffs2, degree2, result);
    
    // Выводим
    printf("=== Умножение многочленов ===\n\n");
    print_polynomial(coeffs1, degree1, "P");
    print_polynomial(coeffs2, degree2, "Q");
    printf("\nПроизведение:\n");
    print_polynomial(result, result_degree, "P*Q");
    
    return 0;
}