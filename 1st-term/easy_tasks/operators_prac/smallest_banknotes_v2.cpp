
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

/*
good alternative

int main() {
    // 1. Добавим проверку входных данных
    int total_cash;
    std::cin >> total_cash;
    if (total_cash <= 0) {
        std::cout << "Invalid input: amount should be positive" << std::endl;
        return 1;
    }

    // 2. Сразу отсортируем банкноты по убыванию
    std::vector<int> banknote_values = {100, 50, 10, 5, 2, 1};
    
    // 3. Создадим вектор для хранения результата с известным размером
    std::vector<int> result_vec(banknote_values.size(), 0);

    // 4. Улучшим цикл
    for (size_t i = 0; i < banknote_values.size(); ++i) {
        if (total_cash >= banknote_values[i]) {  // Более понятное условие
            result_vec[i] = total_cash / banknote_values[i];
            total_cash %= banknote_values[i];    // Используем оператор %
            
            // 5. Улучшим вывод
            if (result_vec[i] > 0) {
                std::cout << "Банкнот номиналом " << banknote_values[i] 
                         << ": " << result_vec[i] << std::endl;
            }
        }
    }

    // 6. Проверка на успешность размена
    if (total_cash != 0) {
        std::cout << "Ошибка: не удалось разменять всю сумму" << std::endl;
        return 1;
    }

    return 0;
}
*/