#include<bits/stdc++.h>

using namespace std;

void f(int i,int n,vector<int>& nums,string bitmask,unordered_map<int,vector<string>>& mpp,int sum){
    if(i==n){
        mpp[sum].push_back(bitmask);
        return;
    }

    //take
    string cMask=bitmask;
    cMask+="1";
    f(i+1,n,nums,cMask,mpp,sum+nums[i]);
    //notTake
    cMask[cMask.size()-1]='0';
    f(i+1,n,nums,cMask,mpp,sum);
}

bool isValid(int sum,unordered_map<int,vector<string>>& mpp){
    if(mpp.find(sum)!=mpp.end()){
        vector<string> v=mpp[sum];
        for(int i=0;i<v.size();i++){
            for(int j=i+1;j<v.size();j++){
                //SYNTAX TO REMEMBER !!!!
                int b1 = stoi(v[i], nullptr, 2); // Convert binary string to int
                int b2 = stoi(v[j], nullptr, 2);
                if((b1&b2)==0){
                    return true;
                }
            }
        }
        return false;
    }
    else{
        return false;
    }
}

int main(){
    int t;
    cin>>t;
    for(int i=0;i<t;i++){
        int n;
        cin>>n;
        vector<int> v(n);
        for(int i=0;i<n;i++){
            cin>>v[i];
        }
        unordered_map<int,vector<string>> mpp;
        string str="";
        f(0,n,v,str,mpp,0);

        int l=0,r=accumulate(v.begin(),v.end(),0)/2,mid;
        while(l<=r){
            mid=(l+r)/2;
            if(isValid(mid,mpp)){
                l=mid+1;
            }
            else{
                r=mid-1;
            }
        }
        //IMPORTANT VERY VERY IMPORTANT EDGE CASE
        if(r<0) r=0;
        cout<<r<<endl;
    }
}