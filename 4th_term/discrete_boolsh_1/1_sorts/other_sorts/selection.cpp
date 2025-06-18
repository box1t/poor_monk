
// try to implement on vector, on list

#include <iostream>

void selection_sort(int arr[], int n) {
    for (int i = 0; i < n-1; ++i) {
        int min_index = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
                std::cout << "MIN INDEX IS: " << min_index << "\n";
                std::cout << "Element of that index is: " << arr[min_index] << "\n";
            }
        }
        if (min_index != i) {
            std::swap(arr[i], arr[min_index]);
        }
        std::cout << "Element moved forward during iteration: " << arr[i] << "\n";
        std::cout << "Res after iteration: " << "\n";
        for (int i = 0; i < n; ++i) {
            std::cout << arr[i] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "AFTER USING SELECTION SORT" << "\n";
    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";

}

int main()
{
    int arr[] = {13, 46, 24, 52, 20, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    std::cout << "Before Using Selection Sort: " << std::endl;
    for (int i = 0; i < n; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    selection_sort(arr, n);
    return 0;
}

