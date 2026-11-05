// Write a C program that accepts two integer values and calculates the sum of all even values between them.

#include <stdio.h>

int main() {
    int n1, n2;
    scanf("%d %d", &n1, &n2);
    int sum_even = 0;
    if (n1 > n2) {
        int temp = n1;
        n1 = n2;
        n2 = temp;
    }

    for (int i = n1; i < n2; ++i) {
        if (i % 2 == 0) {
            sum_even += i;
            printf("%d ", i);
        }
    }
    printf("\n%d", sum_even);
    
}