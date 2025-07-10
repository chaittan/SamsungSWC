#include<bits/stdc++.h>

using namespace std;

void f(string input){
    int n=input.size();
    map<char,int> mpp;
    int i=0;
    for(i=0;i<n;i++){
        char c=input[i];
        i++;
        int num=0;
        while(i<n&&input[i]>='0'&&input[i]<='9'){
            int digit=input[i]-'0';
            num=num*10+digit;
            i++;
        }
        i--;
        mpp[c]+=num;
    }

    for(auto it:mpp){
        if(it.second!=0)    cout<<it.first<<" "<<it.second<<" ";
    }
    cout<<endl;
}

int main(){
    int t;
    cin>>t;
    for(int i=0;i<t;i++){
        string input;
        cin>>input;
        f(input);
    }
    return 0;
}