#include<bits/stdc++.h>

using namespace std;

class Solution {
    int f(int l,int r,vector<int>& nums,vector<vector<int>>& dp ){
        if(l>r) return 0;
        if(dp[l][r]!=-1) return dp[l][r];
        for(int i=l;i<=r;i++){
            int coins= nums[l-1]*nums[i]*nums[r+1];
            coins+= f(l,i-1,nums,dp)+f(i+1,r,nums,dp);
            dp[l][r]=max(dp[l][r],coins);
        }
        return dp[l][r];
    }
public:
    int maxCoins(vector<int>& nums) {
        int n=nums.size();

        vector<int> numsC(n+2);
        numsC[0]=1;
        numsC[n+1]=1;
        for(int i=1;i<=n;i++){
            numsC[i]=nums[i-1];
        }
        vector<vector<int>> dp(n+2,vector<int>(n+2,-1));
        return f(1,n,numsC,dp);
    }
};