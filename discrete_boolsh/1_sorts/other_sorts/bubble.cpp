#include <iostream>
#include <vector>

std::vector<int> bubbleSort(std::vector<int> numbers) {
    for (int i = numbers.size(); i >=0; i--) {
        for (int j = 1; j <= i; ++j) {
            if (numbers[j - 1] > numbers[j]) {
                std::swap(numbers[j - 1], numbers[j]);
            }
        }
    }
    return numbers;
}

int main(){
    std::vector<int> vec_uns{4,6,2,3,7,1};
    std::vector<int> sorted = bubbleSort(vec_uns);
    for (int name : sorted) {
        std::cout << name << " ";
    }  
}


