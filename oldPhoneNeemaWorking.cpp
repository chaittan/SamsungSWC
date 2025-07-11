#include <iostream>
#include<bits/stdc++.h>
using namespace std;
using ll = long long;  // global alias
int n,m,o;
vector<int> nums, ops;
int ans=INT_MAX;
int cnt=1;
int eval(int prev,int curr,int op){
    if(prev==-1e5)return curr;
    if(op==1){
        return prev+curr;
    }
    else if(op==2){
        return prev-curr;
    }
    else if(op==3){
        return prev*curr;
    }
    else if(op==4){
        if(curr!=0) return prev/curr;
        return -1e9;
    }
    else{
        return -1e9;
    }
}
void cal(int prev,int curr,int op,int touches,int target){
    if(touches>ans || touches>o) return;
    // Case 1
    if(curr!=-1e5 && op!=-1){
        if(curr==0 && op==4){

        }
        else{
           
            int res=eval(prev,curr,op);
            
            if(res==target){
                // if(cnt==5){
                //     cout<<"Block 1 "<<endl;
                // cout<<"Prev "<<prev<<endl;
                // cout<<"Curr "<<curr<<endl;
                // cout<<"Res "<<res<<endl;
                // cout<<"Target "<<target<<endl;
                // }
                ans=min(touches+1,ans);
            }
        }
    }

    // Case 2
    if(curr==target && prev==-1e5 && op==-1){
        ans=min(touches,ans);
    }

    if(prev==target && curr==-1e5 && op==-1){
        ans=min(touches,ans);
    }
    


    for(int i=0;i<m;i++){
        if(curr==-1e5) break;
        if(curr==0 && op==4) break;
        int result=eval(prev,curr,op);
        if(result!=-1e9){
            cal(result,-1e5,ops[i],touches+1,target);
        }

    }
    for(int i=0;i<n;i++){
        int digit=nums[i];
        if(curr==-1e5){
            // if(cnt==5 && digit==1){
            //     cout<<"toches "<<touches<<endl;
            // }
            cal(prev,digit,op,touches+1,target);
        }
        else{
            // if(cnt==5 && curr==1 && digit==8){
            //     cout<<touches<<endl;
            // }
            int t=abs(curr)*10+digit;
            
            if(curr<0) t=t*-1;
            cal(prev,t,op,touches+1,target);
        }
    }
}
void solve(){
    
    cin>>n>>m>>o;
    ans=INT_MAX;
    nums.resize(n);
    ops.resize(m);
    for(int i=0;i<n;i++){
        cin>>nums[i];
    }
    
    for(int i=0;i<m;i++){
        cin>>ops[i];
    }
    int target;
    cin>>target;
    cout<<"I have entered target = "<<target<<endl;
    // cout<<cal(-1e5,1e5,-1,0,target);
    cal(-1e5,-1e5,-1,0,target);
    if(ans==INT_MAX){
        cout<<-1<<endl;
    }
    else{
        cout<<ans<<endl;
    }
    cnt++;
}
int main(){
    int t;
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
}
