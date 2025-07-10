#include<iostream>
#include<algorithm>
using namespace std;

void f(int i, int j, int val,int & ans, int arr[10][5], bool bombUsed, int rowsSafe){
    if(i<0||j<0||j>4){
        ans=max(ans,val);
        return;
    }

    if(arr[i][j]==0||arr[i][j]==1){
        int newCoins=val;
        if(arr[i][j]==1) newCoins++;
        if(bombUsed) rowsSafe--;
        f(i-1,j-1,newCoins,ans,arr,bombUsed,rowsSafe);
        f(i-1,j,newCoins,ans,arr,bombUsed,rowsSafe);
        f(i-1,j+1,newCoins,ans,arr,bombUsed,rowsSafe);
    }
    else{
        if(bombUsed&&rowsSafe>0){
            rowsSafe--;
            f(i-1,j-1,val,ans,arr,bombUsed,rowsSafe);
            f(i-1,j,val,ans,arr,bombUsed,rowsSafe);
            f(i-1,j+1,val,ans,arr,bombUsed,rowsSafe);
        }
        else if(bombUsed&&rowsSafe<=0){
            ans=max(ans,val);
            return;
        }
        else{
            f(i-1,j-1,val,ans,arr,true,4);
            f(i-1,j,val,ans,arr,true,4);
            f(i-1,j+1,val,ans,arr,true,4);
        }
    }
}

int main(){
    int t;
    cin>>t;
    for(int i=0;i<t;i++){
        int n;
        cin>>n;
        int arr[10][5];
        for(int i=0;i<n;i++){
            for(int j=0;j<5;j++){
                cin>>arr[i][j];
            }
        }
        int ans=-1*1e9;
        f(n-1,2,0,ans,arr,false,0);
        f(n-1,1,0,ans,arr,false,0);
        f(n-1,3,0,ans,arr,false,0);
        cout<<ans<<endl;
    }
    return 0;
}