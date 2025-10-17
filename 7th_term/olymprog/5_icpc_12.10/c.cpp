
#include <bits/stdc++.h>

using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int64_t> vec(14);
    for (int l = 0; l < vec.size(); ++l) {
        int64_t t;
        cin >> t;
        
        vec[l] = static_cast<int64_t>(round(t * 10));
    }
    int64_t n = 1;
    
    while (true) {
        bool flag = true;
        for (int i = 0; i < 14; ++i){
            // cout << abs(n * vec[i] / 100 - round(n * vec[i] / 100)) << " " << n * vec[i] / 100 << endl;
            if ((n * vec[i]) % 1000 != 0) {
                flag = false;
                break;
            }
        }
        if (flag) {
            cout << n;
            break;
        }
        
        n += 1;
    }
}