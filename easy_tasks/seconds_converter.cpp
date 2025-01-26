#include <iostream>

int main() {
    int seconds;
    int minutes;
    int hours;

    std::cin >> seconds;

    hours = seconds / 3600; // почему целая часть выделяется здесь сама?
    minutes = (seconds % 3600 / 60);
    seconds = (seconds % 3600 % 60);

    std::cout << '\n' << hours << '\n' << minutes << '\n' << seconds << '\n';
}
