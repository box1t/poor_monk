

void counting_sort(std::vector<Sortable_Data>& input_vec, unsigned long long exp) {

    int size = input_vec.size();
    std::vector<int> count(10, 0);
    std::vector<Sortable_Data> result_vec(size);

    for (const auto& item : input_vec) {
        int digit = (item.key / exp) % 10;
        ++count[digit];
    }

    for (int i = 1; i < 10; ++i) {
        count[i] += count[i - 1];
    }

    for (int i = size - 1; i >= 0; --i) {
        int digit = (input_vec[i].key / exp) % 10;
        result_vec[count[digit] - 1] = input_vec[i]; 
        --count[digit];
    }

    std::copy(result_vec.begin(), result_vec.end(), input_vec.begin());
}

void radix_sort(std::vector<Sortable_Data>& input_vec, unsigned long long max_element) {
    for (unsigned long long exp = 1; max_element / exp > 0; exp *= 10) { 
        counting_sort(input_vec, exp);
    }
}
