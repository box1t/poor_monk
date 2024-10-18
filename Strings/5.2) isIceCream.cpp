#include <iostream>
#include <string>

bool isIce(const std::string& other) {
    int substring_changes_counter = 0;

    for (int i = 0; i < other.length() - 1; ++i) {
        if (other[i] != other[i + 1]) {
            ++substring_changes_counter;
        }    
    }
    if (substring_changes_counter < 2) {
        return false;
    }

    for (int i = 0; i < other.length(); ++i) {
        if(other[i] != other[other.length() - i - 1]) {
            return false;
        }
    }
    return true;
}

int main() {
    std::string str;
    std::cout << "Enter a string";
    std::cin >> str;
    while(str.length() < 3 || !isIce(str)) {
        std::cout << "Enter a valid string (length >=3)";
        std::getline(std::cin, str);
    }
    std::cout << "True\n\n";
    return 0;
}
