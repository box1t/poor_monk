
// Break amount into smallest banknotes

#include <iostream>
#include <vector>

int main() {
    int total_cash;
    std::cin >> total_cash;
    std::vector<int> banknote_values = {1, 2, 5, 10, 50, 100};
    std::vector<int> result_vec;

    // Прямой обход
    // for (int i = 0; i < banknote_values.size(); ++i) {
    //     if (total_cash / banknote_values[i] > 0) {
    //         int result_of_division = total_cash / banknote_values[i];
    //         result_vec.push_back(result_of_division);
    //         total_cash -= banknote_values[i] * result_of_division;
    //         std::cout << banknote_values[i] << " : " << result_of_division << std::endl;
    //     }
    // }

    // Обратный обход
    for (int i = banknote_values.size() - 1; i > 0; --i) {
        if (total_cash / banknote_values[i] > 0) {
            int result_of_division = total_cash / banknote_values[i];
            result_vec.push_back(result_of_division);
            total_cash = total_cash - banknote_values[i] * result_of_division;
            std::cout << banknote_values[i] << " : " << result_of_division << std::endl; 
        }
    }
}