#include <iostream>
#include <string>
#include <cmath> // Для std::pow, хотя лучше реализовать свою integer power

// Функция для вычисления степени (base^exp)
// Используем long long для предотвращения переполнения для больших чисел
long long power(long long base, int exp) {
    long long res = 1;
    for (int i = 0; i < exp; ++i) {
        res *= base;
    }
    return res;
}

void factorizeBinomial(long long a, long long b, int n, char operation) {
    std::cout << "\n--- Разложение " << a << "^" << n << " " << operation << " " << b << "^" << n << " ---" << std::endl;

    long long binomialValue;
    if (operation == '+') {
        binomialValue = power(a, n) + power(b, n);
    } else if (operation == '-') {
        binomialValue = power(a, n) - power(b, n);
    } else {
        std::cout << "Некорректная операция. Используйте '+' или '-'." << std::endl;
        return;
    }

    std::cout << "Исходное значение двучлена: " << binomialValue << std::endl;

    if (operation == '-') { // Формула для a^n - b^n
        if (n == 0) {
            std::cout << "Нельзя разложить на множители при n=0 по данной формуле." << std::endl;
            return;
        }

        long long factor1 = (a - b);
        long long factor2Sum = 0;
        std::string factor2_terms_str = "";

        for (int i = 0; i < n; ++i) {
            long long term = power(a, n - 1 - i) * power(b, i);
            factor2Sum += term;
            factor2_terms_str += (i == 0 ? "" : " + ") + std::to_string(a) + "^" + std::to_string(n - 1 - i) + "*" + std::to_string(b) + "^" + std::to_string(i);
        }
        
        long long factor2 = factor2Sum;
        
        std::cout << "Факторизация: (" << a << " - " << b << ") * (" << factor2_terms_str << ")" << std::endl;
        std::cout << "Полученные множители: (" << factor1 << ") * (" << factor2 << ")" << std::endl;

        long long productOfFactors = factor1 * factor2;
        std::cout << "Произведение множителей: " << productOfFactors << std::endl;
        if (productOfFactors == binomialValue) {
            std::cout << "Проверка успешна: " << productOfFactors << " == " << binomialValue << std::endl;
        } else {
            std::cout << "Проверка не удалась: " << productOfFactors << " != " << binomialValue << std::endl;
        }

    } else if (operation == '+') { // Формула для a^n + b^n
        if (n % 2 != 0) { // n нечетное
            long long factor1 = (a + b);
            long long factor2Sum = 0;
            std::string factor2_terms_str = "";

            for (int i = 0; i < n; ++i) {
                long long term = power(a, n - 1 - i) * power(b, i);
                if (i % 2 == 1) { // Чередуем знаки
                    factor2Sum -= term;
                    factor2_terms_str += " - ";
                } else {
                    factor2Sum += term;
                    if (i != 0) factor2_terms_str += " + ";
                }
                factor2_terms_str += std::to_string(a) + "^" + std::to_string(n - 1 - i) + "*" + std::to_string(b) + "^" + std::to_string(i);
            }
            
            long long factor2 = factor2Sum;

            std::cout << "Факторизация: (" << a << " + " << b << ") * (" << factor2_terms_str << ")" << std::endl;
            std::cout << "Полученные множители: (" << factor1 << ") * (" << factor2 << ")" << std::endl;

            long long productOfFactors = factor1 * factor2;
            std::cout << "Произведение множителей: " << productOfFactors << std::endl;
            if (productOfFactors == binomialValue) {
                std::cout << "Проверка успешна: " << productOfFactors << " == " << binomialValue << std::endl;
            } else {
                std::cout << "Проверка не удалась: " << productOfFactors << " != " << binomialValue << std::endl;
            }
        } else { // n четное
            if (n > 2) {
                 std::cout << "Для " << a << "^" << n << " + " << b << "^" << n << " при четном n=" << n << " > 2, этот двучлен не раскладывается на линейные множители согласно указанным формулам." << std::endl;
            } else if (n == 2) { // a^2 + b^2 - не раскладывается в действительных числах
                 std::cout << "Для " << a << "^" << n << " + " << b << "^" << n << " при четном n=" << n << ", этот двучлен не раскладывается на линейные множители в действительных числах." << std::endl;
            } else if (n == 0) {
                std::cout << "Нельзя разложить на множители при n=0 по данной формуле." << std::endl;
            }
        }
    }
}

int main() {
    long long a, b;
    int n;
    char operation;

    std::cout << "Введите основание a: ";
    std::cin >> a;
    std::cout << "Введите основание b: ";
    std::cin >> b;
    std::cout << "Введите степень n: ";
    std::cin >> n;
    std::cout << "Введите операцию (+ или -): ";
    std::cin >> operation;

    factorizeBinomial(a, b, n, operation);

    // Дополнительные примеры для тестирования:
    factorizeBinomial(2, 3, 4, '-');
    factorizeBinomial(2, 3, 4, '+');
    factorizeBinomial(2, 3, 3, '+'); // Пример для нечетного n
    factorizeBinomial(5, 2, 5, '-');
    factorizeBinomial(4, 3, 2, '+'); // Пример a^2 + b^2
    factorizeBinomial(1, 1, 0, '-'); // Пример n=0
    factorizeBinomial(1, 1, 0, '+'); // Пример n=0

    return 0;
}