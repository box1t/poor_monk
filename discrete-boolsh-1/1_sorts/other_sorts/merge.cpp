#include <vector>
#include <iostream>

void merge(std::vector<int>& vec, int low, int mid, int high);

std::vector<int> merge_sort(std::vector<int>& vec, int low, int high) {
    if (low < high) {
        int mid = (low + high)/2;
        merge_sort(vec, low, mid);
        merge_sort(vec, mid + 1, high);
        merge(vec, low, mid, high);
    }
    return vec;
}
 
void merge(std::vector<int>& vec, int low, int mid, int high) {
    std::vector<int> b;
    for (int i = low; i <= high; ++i) {
        b.push_back(vec[i]);
    }
    int l = low;
    int r = mid + 1;
    int i = low;
    while (l <= mid && r < high) {
        if (b[l - low] <= b[r - low]) {
            vec[i] = b[l - low];
            l += 1;
        }
        else {
            vec[i] = b[r - low];
            r += 1;
        }
        i += 1;
    }
    while (l <= mid) {
        vec[i] = b[l - low];
        l += 1;
        i += 1;
    }
    while (r <= high) {
        vec[i] = b[r - low];
        r += 1;
        i += 1;
    }
}

int main() {
    std::vector<int> vec_uns{4,6,2,3,7,1};
    merge_sort(vec_uns, 0, vec_uns.size() - 1);
    for (int name : vec_uns) {
        std::cout << name << " ";
    }  
    std::cout << std::endl;
}
