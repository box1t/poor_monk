
// Find the difference between max and min of 4 numbers


/*
Алгоритм решения:
- написать свой max
- написать свой min
- циклом применить max, min, актуализировать значения без размыкания всего множества переменных.

- но что значит циклом, если переменные стоят отдельно?
- может, если указано конкретное число, имели ввиду именно решение ветвистое?

- да, у них тоже ветвистое, притом моё компактнее.

*/


#include <stdio.h>

int main() {
    int one, two, three, four;
    scanf("%d%d%d%d", &one, &two, &three, &four);

    int min = one;
    int max = four;
    if (two < min) {
        min = two;
    }
    if (three < min) {
        min = three;
    }
    if (four < min) {
        min = four;
    }
    if (one > max) {
        max = one;
    }
    if (two > max) {
        max = two;
    }
    if (three > max) {
        max = three;
    }
    int res = max - min;
    
    printf("%d", res);
}
