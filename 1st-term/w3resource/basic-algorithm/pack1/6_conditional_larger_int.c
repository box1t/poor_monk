// Write a C program to find the larger of two given integers. 
// However if the two integers have the same remainder when divided by 5, choose the smaller integer. 
// If the two integers are the same, return 0. 

#include <stdio.h>

int chose_int(int n1, int n2) {
    if (n1 == n2) {
        return 0;
    }
    if (n1 % 5 == n2 % 5) {
        if (n1 > n2) {
            return n2;
        }
        return n1;
    }
    if (n1 > n2) {
        return n1;
    }
    return n2;
}


int main() {
    int n1 = 10;
    int n2 = 10;
    printf("Chosen int is %d", chose_int(n1, n2));
}