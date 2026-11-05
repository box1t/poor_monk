// calculator. Write a Program, that takes two numbers and an operator (+, -, /, *, %) as input and prints the result.
// Experts: The program should also accept the words add, substract, multiply, divide and remainder as operators.

#include <stdio.h>
#include <string.h>

int main() {
    int n1, n2;
    char op[20]; // Буфер для оператора (символа или слова)

    // Читаем два числа и оператор как строку
    if (scanf("%d %d %19s", &n1, &n2, op) != 3) {
        printf("Invalid input\n");
        return 1;
    }

    // Сложение
    if (strcmp(op, "+") == 0 || strcmp(op, "add") == 0) {
        printf("%d\n", n1 + n2);
    }
    // Вычитание
    else if (strcmp(op, "-") == 0 || strcmp(op, "substract") == 0) {
        printf("%d\n", n1 - n2);
    }
    // Умножение
    else if (strcmp(op, "*") == 0 || strcmp(op, "multiply") == 0) {
        printf("%d\n", n1 * n2);
    }
    // Деление (с проверкой на ноль!)
    else if (strcmp(op, "/") == 0 || strcmp(op, "divide") == 0) {
        if (n2 == 0) {
            printf("Error: Division by zero\n");
        } else {
            printf("%d\n", n1 / n2);
        }
    }
    // Остаток от деления (с проверкой на ноль!)
    else if (strcmp(op, "%") == 0 || strcmp(op, "remainder") == 0) {
        if (n2 == 0) {
            printf("Error: Division by zero\n");
        } else {
            printf("%d\n", n1 % n2);
        }
    }
    // Неизвестный оператор
    else {
        printf("Unknown operator\n");
    }

    return 0;
}