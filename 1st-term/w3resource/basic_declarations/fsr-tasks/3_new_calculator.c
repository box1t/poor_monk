// Take the calculator task and unburden the switch by adding functions for each operation.
#include <stdio.h>
#include <string.h>

// Возвращаем int: 1 если оператор обработан, 0 если нет
int try_add(const char *op, int n1, int n2) {
    if (strcmp(op, "+") == 0 || strcmp(op, "add") == 0) {
        printf("%d\n", n1 + n2);
        return 1; // Успех (true)
    }
    return 0; // Не мой оператор (false)
}

int try_subtract(const char *op, int n1, int n2) {
    if (strcmp(op, "-") == 0 || strcmp(op, "subtract") == 0) {
        printf("%d\n", n1 - n2);
        return 1;
    }
    return 0;
}

int try_multiply(const char *op, int n1, int n2) {
    if (strcmp(op, "*") == 0 || strcmp(op, "multiply") == 0) {
        printf("%d\n", n1 * n2);
        return 1;
    }
    return 0;
}

int try_divide(const char *op, int n1, int n2) {
    if (strcmp(op, "/") == 0 || strcmp(op, "divide") == 0) {
        if (n2 == 0) {
            printf("Error: Division by zero\n");
        } else {
            printf("%d\n", n1 / n2);
        }
        return 1;
    }
    return 0;
}

int try_remainder(const char *op, int n1, int n2) {
    if (strcmp(op, "%") == 0 || strcmp(op, "remainder") == 0) {
        if (n2 == 0) {
            printf("Error: Division by zero\n");
        } else {
            printf("%d\n", n1 % n2);
        }
        return 1;
    }
    return 0;
}

int main() {
    int n1, n2;
    char op[20];

    if (scanf("%d %d %19s", &n1, &n2, op) != 3) {
        printf("Invalid input\n");
        return 1;
    }

    // В C условие if (1) выполняется, а if (0) пропускается.
    // Поэтому код в main остается таким же чистым и красивым.
    if (try_add(op, n1, n2)) return 0;
    if (try_subtract(op, n1, n2)) return 0;
    if (try_multiply(op, n1, n2)) return 0;
    if (try_divide(op, n1, n2)) return 0;
    if (try_remainder(op, n1, n2)) return 0;

    // Если ни одна функция не вернула 1, значит оператор неизвестен
    printf("Unknown operator\n");

    return 0;
}