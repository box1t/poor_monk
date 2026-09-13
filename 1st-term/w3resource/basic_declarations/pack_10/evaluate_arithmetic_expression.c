// Write a C program that reads an expression and evaluates it.

/* 
The expression consists of numerical values, operators and parentheses, and the ends with '='.
The operators includes +, -, *, / where, represents, addition, subtraction, multiplication and division.
When two operators have the same precedence, they are applied to left to right.
You may assume that there is no division by zero.
All calculation is performed as integers, and after the decimal point should be truncated
Length of the expression will not exceed 100.
*/

#include <stdio.h>
#include <ctype.h>

char expr[101];
int pos = 0;


// Читает число или выражение в скобках
int factor() {

    int result = 0;

    // Если встретили '('
    if (expr[pos] == '(') {

        pos++; // пропускаем '('

        result = expression();

        pos++; // пропускаем ')'
    }

    else {

        while (isdigit(expr[pos])) {

            result = result * 10 + (expr[pos] - '0');

            pos++;
        }
    }

    return result;
}


// Умножение и деление
int term() {

    int result = factor();

    while (expr[pos] == '*' || expr[pos] == '/') {

        char op = expr[pos];

        pos++;

        int value = factor();

        if (op == '*') {
            result *= value;
        }
        else {
            result /= value;
        }
    }

    return result;
}


// Сложение и вычитание
int expression() {

    int result = term();


    while (expr[pos] == '+' || expr[pos] == '-') {

        char op = expr[pos];

        pos++;

        int value = term();


        if (op == '+') {
            result += value;
        }
        else {
            result -= value;
        }
    }

    return result;
}


int main() {

    printf("Enter expression: ");

    scanf("%100s", expr);


    printf("Result = %d\n", expression());


    return 0;
}