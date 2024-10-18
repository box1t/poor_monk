/*
Это почти задача на обработку матрицы, но не совсем. а что если так считать?
А что если модифицировать её как матрицу? я же для этого и использую вектор. 
кажется, с вектором она более гибкая и не одноходовая. 

как проверить?
убедиться, можно ли сменой знаков поменять направление обхода.


какие вопросы задать к этому подходу, чтобы его воспроизвести? 
а посмотри на комментарии к коду.


а как воспроизвести ИЗЕВЫЙ? - это нубский подход. причем это ответы хендбука!
то есть надо понять эвристику и заложить в вопрос.

*/




#include <iostream>
#include <vector>
#include <string>

// Заполнение вектора строк с календарём
std::vector<std::string> fill_calendar(int week_day, int days_in_month) {
    std::vector<std::string> lines_vec; // Вектор строк для календаря
    std::string current_line; // Текущая строка для заполнения
    int day_counter = 1;

    // Добавляем пустые места в первую строку до начала первого дня
    for (int i = 1; i < week_day; ++i) {
        current_line += "   "; // Заполняем пробелами
    }

    // Заполнение календаря днями
    while (day_counter <= days_in_month) {
        // Добавляем день в строку
        if (day_counter < 10) {
            current_line += " " + std::to_string(day_counter) + " "; // Добавляем пробел перед однозначным числом
        } else {
            current_line += std::to_string(day_counter) + " "; // Для двузначных чисел пробел не нужен перед числом
        }

        // Если достигли конца недели (7 дней), добавляем строку в вектор и создаём новую
        if ((week_day + day_counter - 1) % 7 == 0) { // довольно странно.
            lines_vec.push_back(current_line);
            current_line.clear(); // Очищаем строку для новой недели
        }

        ++day_counter;
    }

    // Добавляем оставшуюся строку, если она неполная
    if (!current_line.empty()) {
        lines_vec.push_back(current_line);
    }

    return lines_vec;
}

// Печать календаря
void print_calendar(const std::vector<std::string>& calendar_vec) {
    for (const std::string& line : calendar_vec) {
        // Печатаем строку без лишних пробелов в конце
        std::cout << line.substr(0, line.size() - 1) << std::endl;
    }
}

int main() {
    int week_day, days_in_month;
    std::cin >> week_day >> days_in_month;

    // Заполняем календарь
    std::vector<std::string> calendar = fill_calendar(week_day, days_in_month);

    // Выводим календарь
    print_calendar(calendar);

    return 0;
}
