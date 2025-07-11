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

/*
8
a12b3c4
x1x2x10
p0q5r0
z9y
b100a1b2
m12n3m4n5
a1A2a3

a 12 b 3 c 4
x 13
q 5
z 9
a 1 b 102
m 16 n 8
A 2 a 4
*/