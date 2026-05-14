1 2 3 4 5


// Это для вектора. 
std::vector<int> odd_positions(const std::vector& input_vec) {
    std::vector<int> result_vector;
    for (int i = 1; i < input_vec.length(); i += 2) {
        result_vector += input_vec[i];
    }
    return result_vector;
}


// Это для слов в строке

std::string odd_positions(const std::string& input_string) {
    std::string result_string;
    int space_counter = 1;
    for (int i = 0; i < input_string; ++i) {
        if (input_string[i] == " ") {
            ++space_counter;
        }
        if(space_counter % 2 == 0) {
            result_string += input_string.substr(i); // dumay
        }
    }
}