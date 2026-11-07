#include <iostream>
#include <string>
#include <vector>

std::string& ConcatenateStrings(const std::vector<std::string>& concatenation_parts) {
    std::string result;
    for (const auto& part : concatenation_parts) {
        result += part;
    }
    return result;
}

