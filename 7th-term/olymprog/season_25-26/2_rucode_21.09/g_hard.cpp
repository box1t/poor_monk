#include <bits/stdc++.h>

using namespace std;

int main() {
    string q; cin >> q;
    string s;
    cin.ignore();
    char c;
    while (cin.peek() != '\n' && cin.get(c)) {
        s += c;
    }
    if (s.size() && s[0] == ' ') {
        s = s.substr(1);
    }
    string t;
    for (char d : s) {
        if (d != ' ') {
            t += d;
        }
    }
    int n = t.size(), m = q.size();
    vector<int> bad(n);
    for (int i = 0; i + m <= n; ++i) {
        if (t.substr(i, m) == q) {
            for (int j = 0; j < m; ++j) {
                bad[i + j] = 1;
            }
        }
    }
    string u = t;
    for (int i = 0; i < n; ++i) {
        if (bad[i]) {
            for (char d = '0'; d <= '9'; ++d) {
                u[i] = d;
                bool ok = true;
                for (int j = max(0, i - m + 1); j <= i; ++j) {
                    if (j + m <= n && u.substr(j, m) == q) {
                        ok = false;
                        break;
                    }
                }
                if (ok) {
                    break;
                }
            }
        }
    }
    string ans;
    int k = 0;
    for (char d : s) {
        if (d == ' ') {
            ans += ' ';
        } else {
            ans += u[k++];
        }
    }
    for (int i = 0; i < ans.size(); ++i) {
        if (ans[i] == '0' &&
            (i == 0 || ans[i - 1] == ' ') &&
            i + 1 < ans.size() && isdigit(ans[i + 1])) {
            ans[i] = '1';
        }
    }
    cout << ans;
}