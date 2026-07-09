
// Left-shift an integer by two bits

/*
почему обе переменные изменились?
*/

#include <stdio.h>

int main() {
    int variable = 5;
    int var = variable <<= 1;
    printf("%d::%d", var, variable);
}