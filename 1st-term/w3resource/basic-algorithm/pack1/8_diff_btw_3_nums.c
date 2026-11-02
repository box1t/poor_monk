// Write a C program to check three given integers (small, medium and large) and 
// return true if the difference between small and medium and the difference between medium and large is the same. 

#include <stdio.h>

int nums_checker(int n1, int n2, int n3) {
    int small = n1;
    int medium = n2;
    int large = n3;
    int temp;

    if (small > medium) {
        int temp = small; small = medium; medium = temp;
    }
    if (medium > large) {
        int temp = medium; medium = large; large = temp;
    }
    if (small > medium) {
        int temp = small; small = medium; medium = temp;
    }
    if ((medium - small) == (large - medium)) {
        return 1;
    }
    return 0;
}