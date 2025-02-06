#include <iostream>
#include <string>

std::string reverse(const std::string& other) {
    std::string temp_string;
    for (int i = other.size(); i >= 0; --i) { // >= (!!!!)
        temp_string += other[i];
    }
    return temp_string;
}

int main() {
    std::string input_string = "Kafffka";
    std::cout << reverse(input_string);

}
