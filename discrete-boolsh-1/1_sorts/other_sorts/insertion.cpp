#include <vector>
#include <iostream>

void insertion_sort(int arr[], int n) {
    for (int i = 0; i <= n - 1; ++i) {
        int j = i;
        while (j > 0 && arr[j - 1] > arr[j]) {
            std::swap(arr[j-1], arr[j]);
            j--;
            std::cout << "Element moved forward during iteration: " << arr[j + 1] << "\n";
        }
    }
    std::cout << "AFTER USING INSERTION SORT" << "\n";
    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
}
 

int main()
{
    int arr[] = {13, 46, 24, 52, 20, 9};
    // 13 24 46 52 20 9
    // 13 24 46 20 52 9
    // 13 24 20 46 52 9
    // 13 20 24 46 52 9
    // 13 20 24 46 9 52
    // 13 20 24 9 46 52
    // 13 20 9 24 46 52
    // 13 9 20 24 46 52
    // 9 13 20 24 46 52


    int n = sizeof(arr) / sizeof(arr[0]);
    std::cout << "Before Using insertion Sort: " << std::endl;
    for (int i = 0; i < n; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    insertion_sort(arr, n);
    return 0;
}
