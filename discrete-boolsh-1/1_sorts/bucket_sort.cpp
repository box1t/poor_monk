#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> bucket_sort(std::vector<int> arr, int buckets_number) {
    if (arr.empty()) {
        return;
    }
    int min_elem = *std::min_element(arr.begin(), arr.end());
    int max_elem = *std::max_element(arr.begin(), arr.end());

    std::vector<std::vector<int>> buckets_vec(buckets_number);
    double bucket_range = static_cast<double>(max_elem - min_elem + 1) / buckets_number;

    // проходим по входному массиву, вычисляя индексы карманов на его основе, и заполняем buckets_vec
    for (auto data : arr) {
        int bucket_index = static_cast<int>((data - min_elem) / bucket_range);
        if (bucket_index == buckets_number) {
            --bucket_index; // коррекция индекса для максимального элемента. Чтобы что?
        }
        buckets_vec[bucket_index].push_back(bucket_index);
    }

    for (auto& bucket : buckets_vec) {
        std::sort(bucket.begin(), bucket.end());
    }

    std::vector<int> sorted_array;
    for (const auto& bucket : buckets_vec) {
        sorted_array.push_back(bucket);
    }
    return sorted_array;
}

int main() {
    std::vector<int> data = {42, 32, 33, 52, 37, 47, 51};
    int bucketCount = 5;
    std::vector<int> sortedData = bucketSort(data, bucketCount);
    std::cout << "Отсортированный массив: ";
    for (int num : sortedData) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    return 0;
}
