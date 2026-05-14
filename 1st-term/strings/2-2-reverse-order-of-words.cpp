/*
Input string : I love learning programming at Codeforwin

Reversed order of words: 
Codeforwin at programming learning love I
*/



#include <iostream>
#include <string>

std::string reverse_words(const std::string& str) {
    std::string reversed_str;
    size_t start = 0;
    size_t end = str.find(' ', start);
    
    // Перебираем слова в строке и добавляем их в начало результирующей строки
    while (end < str.size()) {
        std::string word = str.substr(start, end - start);
        reversed_str = word + " " + reversed_str;
        start = end + 1;
        end = str.find(' ', start);
    }
    
    // Добавляем последнее слово (или единственное слово, если оно есть)
    std::string last_word = str.substr(start);
    reversed_str = last_word + " " + reversed_str;
    
    return reversed_str;
}

int main() {
    std::string input_string;
    std::cout << "Input string: ";
    std::getline(std::cin, input_string);
    
    std::string reversed_string = reverse_words(input_string);
    
    std::cout << "Reversed order of words: " << reversed_string << std::endl;
    
    return 0;
}




/*
** not working
*
*
*
*
**
*/

// #include <iostream>
// #include <string>

// std::string reverse_words(const std::string& other) {
//     std::string temp_string;
//     int break_counter;
//     for (int i = other.size() - 1; i >= 0; ++i) {
//         if (other[i] == ' ') {
//             ++break_counter;
//             temp_string += other.substr(i, i - 0);
//         }
//     }
//     return temp_string;
// }

// std::string reverse_words(const std::string& other) {
//     std::string temp_string;
//     int break_counter = 0;
//     for (int i = other.size() - 1; i >= 0; --i) {
//         if (other[i] == ' ') {
//             ++break_counter;
//             temp_string += other.substr(i + 1, break_counter - 1);
//             temp_string += " ";
//             break_counter = 0;
//         }
//         if (i == 0) {
//             temp_string += other.substr(i, break_counter + 1);
//         }
//     }
//     return temp_string;
// }

