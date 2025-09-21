#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int64_t n, m;

    if (!(cin >> n >> m)) {
        return 0;
    }

    int64_t mx = n * (n - 1) / 2;
    if (m > mx) {
        cout << -1;
        return 0;
    }

    int64_t dmin;
    if (m >= n - 1) {
        dmin = 1;
    } else {
        dmin = n - m;
    }

    int64_t dmax;
    if (m == 0) {
        dmax = n;
    } else {
        int64_t t = 1;
        while (t * (t - 1) / 2 < m) {
            ++t;
        }
        dmax = n - t + 1;
    }

    cout << dmin << " " << dmax;
}
