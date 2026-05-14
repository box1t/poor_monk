#include <iostream>
#include <vector>
#include <algorithm>

int generate_permutations(std::vector<int>& permutation) {
    int count = 1;
    std::vector<int> count_vec(permutation.size(), 0);
    
    while (true) {
        int i = 0;
        while (i < permutation.size()) {
            if (count_vec[i] < i) {
                if (i % 2 == 0) {
                    std::swap(permutation[0], permutation[1]);
                } else {
                    std::swap(permutation[count_vec[i]], permutation[i]);
                }
                count++;
                count_vec[i]++;
                i = 0;
            } else {
                count_vec[i] = 0;
                i++;
            }
        }
        break;
    }
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

