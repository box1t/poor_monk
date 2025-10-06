// A-task-21.09

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b;
    cin >> a >> b;

    int r = a % b;
    int first = (r * 10) / b;

    cout << first << "\n";
}
