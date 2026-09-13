
// Write a C program that accepts integers 
// from the user until a zero or a negative number, 
// displays the number of positive values, the minimum value, the maximum value, and the average value.

/*
1. Решить циклом
- for - break - с какого конца - что есть граница
- while - нужен ли break? - с какого конца - что есть граница
почему скорее while? тут намек untill, притом единственное ограничение в условии.
    - как выполнить проверку на неотрицательность числа до входа в цикл, если я хочу каждый раз узнавать эту инфу о числе? 



- если надо посчитать ещё и среднее, можно это сохранять!
*/

#include <stdio.h>

int main() {
    int input_var, min, max, positives_counter, sum;
    double avg;
    min = input_var; 
    max = input_var;
    while (input_var > 0) {
        if (input_var < min) {
            min = input_var;
        }
        if (input_var > max) {
            max = input_var;
        }
        sum += input_var;
        ++positives_counter; // в данном случае до выхода из блока переменная успеет обновиться и не произойдет деления на 0 на первой итерации?
    }
    avg = sum / positives_counter; // деление на 0.
    printf("max_val::[%d]\n\nmin_val::[%d]\n\navg::[%f]\n\npositives_counter::[%d]", max, min, avg, positives_counter);
}