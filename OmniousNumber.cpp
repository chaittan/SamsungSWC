#include<iostream> 

using namespace std;

int countValidNumbers(int l, int r, int k, int arr[],int n){
    int ans=0;
    for(int i=l;i<=r;i++){
        int freq[10]={};
        int num=i,count=0;
        while(num){
            freq[num%10]++;
            num/=10;
        }

        for(int i=0;i<n;i++){
            count+=freq[arr[i]];
        }

        if(count<k) ans++;
    }
    return ans;
}

int main(){
    int l,r,k,n;
    cin>>l>>r>>k>>n;
    int arr[n];
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }

    cout<<countValidNumbers(l,r,k,arr,n);
    return 0;
}