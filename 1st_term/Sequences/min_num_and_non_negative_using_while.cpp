/*
Напишите программу, которая определяет минимальное число в последовательности положительных чисел, которую ввел пользователь. 
Если в последовательности есть отрицательные числа, то вы должны сообщить об этом пользователю и предложить повторить ввод еще раз.
*/

int min_positive_number_detection(std::vector<int> vec) {
    int min = vec[0];
    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] < min) {
            min = vec[i];
        }
        else if (i < 0) {
            std::cout << "Negative number found. Please enter again!";
            // break - continue
        }
        // чтобы это сработало, нужен while, потому что выход из for ведет к концу программы? 
        
    }
    return min;
}

int main() {
    std::vector<int> user_vec;
    int vec_length;
    int user_number;
    std::cin >> vec_length;
    user_vec.resize(vec_length);
    for (int i = 0; i < vec_length; ++i) {
        std::cin >> user_number; 
    }
    std::cout << min_positive_number_detection(user_vec);
}



// стоит ли разделить функционал проверки числа на отрицательность и вычисление минимального в последовательности? 

















#include <iostream>
#include <vector>

int main() {
    std::vector<int> input_numbers;
    int number;

    // Считываем числа, пока не встретим отрицательное число
    while (true) {
        std::cout << "Enter a non-negative number (or a negative number to stop): ";
        std::cin >> number;

        if (number < 0) {
            std::cout << "Negative number detected. Exiting input loop.\n";
            break;
        }

        input_numbers.push_back(number);
    }

    if (input_numbers.empty()) {
        return 1;
    }

    // Находим минимальное значение
    int min = input_numbers[0];
    for (int i = 1; i < input_numbers.size(); ++i) {
        if (input_numbers[i] < min) {
            min = input_numbers[i];
        }
    }

    // Выводим минимальное значение
    std::cout << "The minimum non-negative number entered is: " << min << std::endl;

    return 0;
}









