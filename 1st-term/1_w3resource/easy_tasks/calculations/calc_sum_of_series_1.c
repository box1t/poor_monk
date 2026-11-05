
// Calculate the sum of the series 1+1/2+1/3+...+1/n

/*
1.
Задача о применении формулы в цикле.
- найди ошибку у себя сам.

2.
переменная n задаётся вручную, параметризует ряд.

*/

#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    double res;
    for (size_t i = 1; i <= n; ++i) {
        res += 1. / n;
    }
    printf("%f::%d", res, n);
}