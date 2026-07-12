// Write a C program to track and display all positions where the highest value occurs in the input list.

#include <stdio.h>

int main() {
    int n;
    int max;
    int positions[100];
    int count = 0;
    int index = 0;

    while (scanf("%d", &n) == 1) {
        index++;

        if (index == 1) {
            max = n;
            positions[0] = index;
            count = 1;
        }
        else if (n > max) {
            max = n;

            count = 1;
            positions[0] = index;
        }
        else if (n == max) {
            positions[count] = index;
            count++;
        }
    }

    printf("Maximum = %d\n", max);
    printf("Positions: ");

    for (int i = 0; i < count; i++) {
        printf("%d ", positions[i]);
    }

    return 0;
}

//

#include <stdio.h>
#include <limits.h>

int main() {
    int n;

    int max = INT_MIN;
    int positions[100];
    int count = 0;
    int index = 0;

    while (scanf("%d", &n) == 1) {
        index++;

        if (n > max) {
            max = n;

            count = 1;
            positions[0] = index;
        }
        else if (n == max) {
            positions[count] = index;
            count++;
        }
    }

    printf("Maximum = %d\n", max);
    printf("Positions: ");

    for (int i = 0; i < count; i++) {
        printf("%d ", positions[i]);
    }

    return 0;
}