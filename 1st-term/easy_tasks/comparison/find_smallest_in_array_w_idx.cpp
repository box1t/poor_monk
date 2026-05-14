// Write a C program to read an array of length 6 and find the smallest element and its position.

#include <iostream>
#include <vector>


int main() {
    std::vector<int> numbers;
    int input_number;
    for (int i = 0; i < 6; ++i) {
        std::cin >> input_number;
        numbers.push_back(input_number);
    }

    int smallest_index = 0;
    for (int i = 1; i < numbers.size(); ++i) {
        if (numbers[i] < numbers[smallest_index]) {
            smallest_index = i;
        }
    }

    std::cout << "Smallest element: " << numbers[smallest_index] << ", Index: " << smallest_index << std::endl;
}
