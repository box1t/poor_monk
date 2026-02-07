
#include <bits/stdc++.h>

using namespace std;

const int64_t mod = 1e9 + 7;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int64_t n; 
    if(!(cin>>n)) return 0;
    
    int64_t v = 10, c = 20, j = 1, s = 2;
    int64_t dv = v, dc = c, dj = j, ds = 0;

    for (int64_t i = 2; i <= n; ++i){
        int64_t nv = ((dc + dj + ds) % mod) * v % mod;
        int64_t nc = dv * c % mod;
        int64_t nj = dv * j % mod;
        int64_t ns = dc * s % mod;
        dv = nv; dc = nc; dj = nj; ds = ns;
    }
    cout << ((dv + dc) % mod + (dj + ds) % mod) % mod;
}
