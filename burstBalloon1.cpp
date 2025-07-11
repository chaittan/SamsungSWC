#include<bits/stdc++.h>

using namespace std;

int f(int l,int r, vector<int>& v,vector<vector<int>>& dp){
    int n=v.size();
    if(l+1==r) return 0;
    int maxCoins=-1;
    if(dp[l][r]!=-1) return dp[l][r];
    for(int k=l+1;k<r;k++){
        int coins=-1;
        if(l==0&&r==n-1){
            coins=v[k];
        }
        else{
            coins=v[l]*v[r];
        }

        maxCoins=max(maxCoins,coins+f(l,k,v,dp)+f(k,r,v,dp));
    }
    return dp[l][r]=maxCoins;
}

int main(){
    int n;
    cin>>n;
    vector<int> v(n+2,1);
    for(int i=1;i<=n;i++ ){
        cin>>v[i];
    }
    vector<vector<int>> dp(n+2,vector<int>(n+2,-1));
    
    cout<<f(0,n+1,v,dp);
}