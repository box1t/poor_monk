#include <bits/stdc++.h>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<uint64_t>a(n);
    for(int i=0;i<n;i++)cin>>a[i];
    uint64_t A=a[0],X=a[0];
    for(int i=1;i<n;i++){A&=a[i];X^=a[i];}
    if(A&&X){cout<<0;return 0;}
    uint64_t ans=1e18;
    for(int i=0;i<n;i++){
        for(int d=-1;d<=1;d+=2){
            if(d==-1 && a[i]==0)continue;
            auto b=a[i]+d;
            uint64_t A2=0,X2=0;
            for(int j=0;j<n;j++){
                uint64_t v=(j==i?b:a[j]);
                if(j==0){A2=v;X2=v;}
                else{A2&=v;X2^=v;}
            }
            if(A2&&X2)ans=min(ans,1ULL);
        }
    }
    if(ans==1e18)ans=2;
    cout<<ans;
}
