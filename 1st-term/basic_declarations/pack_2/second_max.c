// Write a C program to determine the second highest value and its index from a set of integers.

#include <stdio.h>
#include <limits.h>

int main() {
    int n;
    int max = INT_MIN;
    int second_max = INT_MIN;
    int max_pos = 0;
    int second_pos = 0;

    int pos = 0;

    while (scanf("%d", &n) == 1) {
        pos++;

        if (n > max) {
            second_max = max;
            second_pos = max_pos;

            max = n;
            max_pos = pos;
        }
        else if (n > second_max) {
            second_max = n;
            second_pos = pos;
        }
    }

    if (second_pos != 0) {
        printf("Second highest = %d\n", second_max);
        printf("Position = %d\n", second_pos);
    }
    else {
        printf("Not enough numbers");
    }

    return 0;
}
