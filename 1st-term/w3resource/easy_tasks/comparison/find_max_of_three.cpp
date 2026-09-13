
// Write a C program that accepts three integers and finds the maximum of three.

#include <iostream>

int main() {
    int one, two, three;
    std::cin >> one >> two >> three;
    int max = 0;
    if (one > max) {
        max = one;
    } 
    if (two > max) {
        max = two;
    } 
    if (three > max) {
        max = three;
    }
    std::cout << max;
}

