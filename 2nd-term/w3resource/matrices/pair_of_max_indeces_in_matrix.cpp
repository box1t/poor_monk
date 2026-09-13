#include <iostream>
#include <vector>
#include <utility>

std::pair<size_t, size_t> MatrixArgMax(const std::vector<std::vector<int>>& matrix) {
    std::pair<size_t, size_t> argmax_pair = {0, 0};
    int max_value = matrix[0][0]; 

/*
std::cin >> n >> k; // input is  (const vector& matrix)
*/
   

    size_t n = matrix.size();
    size_t k = matrix[0].size();

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < k; ++j) {
            if (matrix[i][j] > max_value) {
                max_value = matrix[i][j];
                argmax_pair = {i, j}; 
            }
        }
    }

    return argmax_pair;
}

/*
            std::cin >> matrix[i][j];                               // input is  (const vector& matrix) 
            if (i > agrmax_pair[0] && j > agrmax_pair[1]) {         // check out syntax
                agrmax_pair[0] = i;
                agrmax_pair[1] = j;
            }

*/  


int main() {
    size_t n, k;
    std::cin >> n >> k; 
    std::vector<std::vector<int>> matrix(n, std::vector<int>(k));

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < k; ++j) {
            std::cin >> matrix[i][j];
        }
    }

    std::pair<size_t, size_t> result = MatrixArgMax(matrix);
    std::cout << result.first << " " << result.second << std::endl;
    return 0;
}