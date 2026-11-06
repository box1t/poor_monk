#include <iostream>

// Declaration of partition function
int partition(int arr[], int low, int high);

void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int p = partition(arr, low, high);
        quick_sort(arr, low, p - 1);
        quick_sort(arr, p + 1, high);
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int j = low;
    for (int i = low; i <= high - 1; ++i) {
        if (arr[i] <= pivot) {
            std::swap(arr[i], arr[j]);
            j += 1;
        }
    }
    std::swap(arr[j], arr[high]);
    return j;
}

int main() {
    int arr[] = {13, 46, 24, 52, 20, 9};
    int n = sizeof(arr) / sizeof(arr[0]);

    // Finding the lowest and highest elements
    int low = arr[0];
    for (int i = 1; i < n; ++i) {
        if (arr[i] < low) {
            low = arr[i];
        }
    }
    int high = arr[0];
    for (int i = 1; i < n; ++i) {
        if (arr[i] > high) {
            high = arr[i];
        }
    }

    std::cout << "Before Using quick Sort: " << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    quick_sort(arr, 0, n - 1); // Passing the correct low and high indices

    std::cout << "After Using quick Sort: " << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
