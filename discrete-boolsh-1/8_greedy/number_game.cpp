#include <iostream>
#include <vector>

std::vector<int> calculate_min_transfer_cost(int n) {
    std::vector<int> transfer_cost_vec(n + 1);
    std::vector<int> operation_types_vec(n + 1);

    for (int current_n = 2; current_n <= n; ++current_n) {
        transfer_cost_vec[current_n] = transfer_cost_vec[current_n - 1] + current_n;
        operation_types_vec[current_n] = 1;

        if (current_n % 2 == 0 && transfer_cost_vec[current_n / 2] + current_n < transfer_cost_vec[current_n]) {
            transfer_cost_vec[current_n] = transfer_cost_vec[current_n / 2] + current_n;
            operation_types_vec[current_n] = 2;
        }
        
        if (current_n % 3 == 0 && transfer_cost_vec[current_n / 3] + current_n < transfer_cost_vec[current_n]) {
            transfer_cost_vec[current_n] = transfer_cost_vec[current_n / 3] + current_n;
            operation_types_vec[current_n] = 3;
        }
    }

    std::cout << transfer_cost_vec[n] << std::endl;
    return operation_types_vec;
}

void print_transformation_sequence(int n, const std::vector<int>& operation_types_vec) {
    int current_n = n;
    while (current_n > 1) {
        switch (operation_types_vec[current_n]) {
            case 1:
                std::cout << "-1";
                --current_n;
                break;
            case 2:
                std::cout << "/2";
                current_n /= 2;
                break;
            case 3:
                std::cout << "/3";
                current_n /= 3;
                break;
        }
        if (current_n != 1) {
            std::cout << " ";
        }
    }
}

int main() {
    int n;
    std::cin >> n;

    std::vector<int> operation_types_vec = calculate_min_transfer_cost(n);
    print_transformation_sequence(n, operation_types_vec);

    return 0;
}
