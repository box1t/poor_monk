
// Write a C program to find a function values of y = x*n, where n is a non-negative integer.

#include <stdio.h>

int main() {
    int arr_size = 10;
    int y[arr_size];
    int x = 0;
    int n = 5;
    printf("=====(x-values)=====(y-values)=====\n");
    while (x < arr_size) {
        
        y[x] = x * n;
        printf("%8d %16d\n", x, y[x]);
        ++x;

    }
    printf("===================================");
}


// Write a C program to evaluate the equation x=y / n where n is a non-negative integer.

/*
#include <stdio.h>

int main() {
    int y_values[] = {0, 5, 10, 15, 20};
    int n = 5;
    
    printf("=====(y-values)=====(x-values)=====\n");
    for (int i = 0; i < n; ++i) {
        int y = y_values[i];
        int x = y / n;
        if (y % n == 0) {
            printf("(%4d)(%14d)\n", y, x);
        } else {
            printf("(%4d)(%14s)\n", y, "No solution");
        }
    }
    printf("===================================\n");
}

*/
