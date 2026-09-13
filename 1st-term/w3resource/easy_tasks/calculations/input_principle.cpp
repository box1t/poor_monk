
// Write a C program that accepts the principle, rate of interest, and time and calculates simple interest.

#include <iostream>

int main() {
    int principle, rate_of_interest, time; 
    float simple_interest; // это объявления МВП

    std::cin >> principle >> rate_of_interest >> time; // это STL
    
    simple_interest = (principle * rate_of_interest * time) / 100.0; // это МВП. а вопрос о 100 и 100.0 это вопрос о приведении типов
    std::cout << simple_interest;

}
