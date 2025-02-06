#include <iostream>
#include <string>

bool is_password_good(const std::string& password) {
    if (password.size() < 8 || password.size() > 14) {
        return false;
    }
    int big_letter_counter = 0;
    int small_letter_counter = 0;
    int digit_counter = 0;
    int literal_counter = 0;

    for (char ch : password) {
        if (ch < 33 || ch > 126) {
            return false; 
        }
        if (ch >= 'A' && ch <= 'Z') {
            big_letter_counter = 1;
        } else if (ch >= 'a' && ch <= 'z') {
            small_letter_counter = 1;
        } else if (ch >= '0' && ch <= '9') {
            digit_counter = 1;
        } else {
            literal_counter = 1; 
        }
    }

    int class_counter = has_upper + has_lower + has_digit + has_special;
    return class_counter >= 3;
}

int main() {
    std::string password;
    std::cin >> password;
    if (is_password_good(password)) {
        std::cout << "YES" << std::endl;
    } else {
        std::cout << "NO" << std::endl;
    }
}