#include <iostream>

int main() {
    int n, k;
    std::cin >> n >> k;
    int counter = n;
    
    for (int i = 1; i < n; ++i) {
        std::cout << "   ";
    }
    for (int day = 1; day <= k; ++day) {
        if (day < 10) {
            std::cout << " ";
        }
        std::cout << day;
        if (counter == 7) {
            std::cout << "\n";
            counter = 1;
        } else {
            std::cout << " ";
            ++counter; 
        }
    }
    if (counter != 1) {
        std::cout << "\n";
    }
}

// что можно сказать про этот подход? как он отличается от моего с векторами?

