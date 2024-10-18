/*
Напишите программу, которая определяет минимальное число в последовательности положительных чисел, которую ввел пользователь. 
Если в последовательности есть отрицательные числа, то вы должны сообщить об этом пользователю и предложить повторить ввод еще раз.
*/

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


/*
#include <iostream>
#include <vector>

int main() {

    std::vector<int> input_numbers;
    
    for (auto iter : input_numbers) { // bad. i cant input from keyboad (why?) bcs i need to fill vec with input
        int min = iter; // should be defined before loop, or it is created during each loop iteration
        std::cin >> iter;
        if (iter < 0) {
            std::cout << "Wrong input! try non-negative number: " << std::endl;
            std::cin >> iter;
        }
        else {
            if ((iter - 0) <= min) { // min was not init yet! (why?)
            // wrong comparison. dont compare with 0. compare with current min
            
                min = iter;
            }

        }
        std::cout << min;
    }
}


*/