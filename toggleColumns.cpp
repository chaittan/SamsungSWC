#include<bits/stdc++.h>

using namespace std;

int main(){
    int n,m,k;
    cin>>n>>m>>k;
    unordered_map<string,int> mpp;
    int arr[n][m];
    for(int i=0;i<n;i++){
        string temp="";
        for(int j=0;j<m;j++){
            cin>>arr[i][j];
            temp+=('0'+arr[i][j]);
        }
        mpp[temp]++;
    }

    int ans=-1;
    for(auto it:mpp){
        int zeroes=0;
        for(char c:it.first){
            if(c=='0') zeroes++;
        }

        if(zeroes<=k&&((k-zeroes)%2==0)){
            ans=max(ans,it.second);
        }
    }
    cout<<ans<<endl;
    return 0;
}

