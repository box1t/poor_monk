#include <iostream>
#include <vector>
#include <algorithm>

int generate_permutations(std::vector<int>& permutation) {
    int count = 1;
    std::vector<int> count_vec(permutation.size(), 0);

    std::cout << "Initial permutation: ";
    for (int x : permutation) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    while (true) {
        int i = 0;
        
        while (i < permutation.size()) {
            std::cout << "i: " << i << ", count_vec[i]: " << count_vec[i] << std::endl;
            
            if (count_vec[i] < i) {
                if (i % 2 == 0) {
                    std::cout << "Swapping: " 
                              << permutation[0] 
                              << " and " 
                              << permutation[1] 
                              << std::endl;
                    
                    std::swap(permutation[0], permutation[1]);
                } else {
                    std::cout << "Swapping: " 
                              << permutation[count_vec[i]] 
                              << " and " 
                              << permutation[i] 
                              << std::endl;
                    
                    std::swap(permutation[count_vec[i]], permutation[i]);
                }
                
                count++;
                count_vec[i]++;
                i = 0;

                std::cout << "After swap: ";
                for (int x : permutation) {
                    std::cout << x << " ";
                }
                std::cout << std::endl;
            } else {
                count_vec[i] = 0;
                i++;
            }
        }
        
        break;
    }

    std::cout << "Total count: " << count << std::endl;
    return count;
}



int main() {
    int n;
    std::cin >> n;

    // Инициализируем вектор от 1 до n
    std::vector<int> permutation;
    for (int i = 1; i <= n; ++i) {
        permutation.push_back(i);
    }

    // Вызов функции генерации перестановок
    int count = generate_permutations(permutation);

    std::cout << count << std::endl;

    return 0;
}

