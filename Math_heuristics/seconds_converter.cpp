// Write a C++/C program to convert a given integer (in seconds) to hours, minutes and seconds.

#include <iostream>


3605 

1 ч
0 м
5 с

total % 60 = 
total / 60 % 60 = ?

total % 3600 =  ?

total / 60 = ?
total % 60 / 60 = ?

total / 3600 = ?

void seconds_to_mins_converter(int number) {
    int seconds = ;
    int minutes = ;
    int hours = ;
    std::cout << "Seconds: " << seconds << std::endl;
    std::cout << "Minutes: " << minutes << std::endl;
    std::cout << "Hours: " << hours << std::endl;
}

int main() {
    int seconds;
    std::cin >> seconds;
    
    std::cout << seconds_to_mins_converter(seconds) << std::endl;

}



