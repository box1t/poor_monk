#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;
    
    while (q--) {
        string str;
        cin >> str;

        int64_t n = str.size(), cur(1), sz(1);    

        while (cur <= n) {
            int64_t start = cur - 1, end = min(n, cur + sz - 1), len = end - start;

            if (cur > end) {
                break;
            }

            sort(str.begin() + start, str.begin() + start + len);
            
            cur = end + 1;
            sz *= 2;
        }

        cout << str << '\n';
    }
}