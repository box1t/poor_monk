
// Reverse array elements by swapping positions

#include <iostream>
#include <vector>

int main() {
    std::vector<int> elements;
    int input_var;

    elements.resize(6, 0);

    for (int i = 0; i < elements.size(); ++i) {
        std::cin >> input_var;
        elements.push_back(input_var); 
    }

    for (int i = 0; i < elements.size(); ++i) {
        std::cout << elements[i] << "-";
        std::swap(elements[i], elements[i + 1]); // как здесь избежать выхода за границы вектора? (i + 1) или (i - 1)
    }

    for (int i = 0; i < elements.size(); ++i) {
        std::cout << "\n" << elements[i]; 
    }
}
