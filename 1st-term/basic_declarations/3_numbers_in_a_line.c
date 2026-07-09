 
// Write a C program to print 3 numbers on a line, starting with 1 and printing n lines. Accept the number of lines (n, integer) from the user.  
#include <stdio.h>

int main() {
    int n;
    int number = 1;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) { // i → где мы находимся (строка). i меняется только после завершения внутреннего цикла.
        for (int j = 1; j <= 3 ; ++j) { // j → какое место внутри строки. j отвечает только за позицию.
            printf("%d ", number); // number → что именно выводим
            number++;
        }
        printf("\n");
    }
}

