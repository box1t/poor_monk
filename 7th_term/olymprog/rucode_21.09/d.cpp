#include <bits/stdc++.h>

using namespace std;

int get_quadrant(int64_t x, int64_t y) {
    if (x > 0 && y > 0) return 1;
    if (x < 0 && y > 0) return 2;
    if (x < 0 && y < 0) return 3;
    if (x > 0 && y < 0) return 4;
    return 5; 
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int64_t x, y, r;
    cin >> x >> y >> r;

    set<int> colors;

    for (int64_t i = x - r; i <= x + r; ++i) {
        int64_t dy_sq = r * r - (i - x) * (i - x);
        if (dy_sq < 0) continue;
        int64_t dy = sqrt(dy_sq);

        int64_t j1 = y - dy, j2 = y + dy;

        colors.insert(get_quadrant(i, j1));
        colors.insert(get_quadrant(i, j2));

        if (i == 0) {
            colors.insert(5);
        }
        if (j1 <= 0 && 0 <= j2) {
            colors.insert(5);
        }

        if (j2 > j1 + 1) {
            colors.insert(get_quadrant(i, y));
        }
    }

    cout << colors.size();
}