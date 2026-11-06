
```c++
#include<iostream>
#include<vector>
#include<thread>

void BubbleSort(std::vector<int>& arr, int start, int end) {
    for(int i=start; i<end; i++) {
        for(int j = i + 1; j<end; j++) {
            if(arr[i]>arr[j]) {
                std::swap(arr[i], arr[j]);
            }
        }
    }
}

void DoubleThread(std::vector<int>& arr) {
    int size = arr.size();
    std::thread t1(BubbleSort, std::ref(arr), 0, size/2);
    std::thread t2(BubbleSort, std::ref(arr), size/2, size);
    
    t1.join();
    t2.join();
}

int main()
{
    std::vector<int> arr{27, 4, 12, 29, 10, 15, 9, 25, 20, 6, 22, 5, 2, 11, 17, 7, 24, 14, 3, 13, 1, 30, 8, 23, 19, 28, 21, 18, 26, 16};
    DoubleThread(arr);
    
    int i = 0;
    int j = arr.size() / 2;
    int k = 0;
    std::vector<int> arra(arr.size());

    while (i < arr.size() / 2 || j < arr.size()) {
        if (i < arr.size() / 2 && j < arr.size()) {
            if (arr[i] < arr[j]) {
                arra[k++] = arr[i++];
            } else {
                arra[k++] = arr[j++];
            }
        } else if (i < arr.size() / 2){
            arra[k++] = arr[i++];
        } else {
            arra[k++] = arr[j++];
        }
    }
    
    for(const auto& n : arra) {
        std::cout<<n<<" ";
    }
    return 0;
}

```