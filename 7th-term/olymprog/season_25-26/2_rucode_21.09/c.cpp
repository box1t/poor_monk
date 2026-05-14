

#include <bits/stdc++.h>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;

    if(!(cin>>n)) return 0;

    string out;

    out.reserve(2*n);

    for(int i = 0; i < n; ++i) { 
        out.push_back('8'); 
        out.push_back('0'); 
    }
    
    cout << out << "\n";
}
