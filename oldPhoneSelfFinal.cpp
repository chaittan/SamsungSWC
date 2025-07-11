#include<bits/stdc++.h>

using namespace std;

int n,m,o;
vector<int> working,operations;
int ans=INT_MAX;

int eval(int prev,int curr,int op){
    if(prev==-100000){
        return curr;
    }
    
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
        if(curr!=0){
            return prev/curr;
        }
        else{
            return -1e5;
        }
    }
    else{
        return -1e5;
    }
}

void dfs(int prev,int curr, int op,int touches,int target){
    //prune
    if(touches>ans||touches>o){
        return ;
    }

    //press equal to scenario-> we should have curr, pending op, and curr not 0 and op 4
    if(curr!=-100000&&op!=-1){
        if(!(curr==0&&op==4)){
            int res=eval(prev,curr,op);
            if(res==target){
                ans=min(ans,touches+1);
            }
        }
    }

    //prev or curr is equal to ans and no pending operation
    if(prev==target&&curr==-100000&&op==-1){
        ans=min(ans,touches);
    }
    if(prev==-100000&&curr==target&&op==-1){
        ans=min(ans,touches);
    }

    //try every possible op

    for(int i=0;i<m;i++){
        if(curr==-100000){
            break;
        }
        if(curr==0&&op==4){
            break;
        }

        int result=eval(prev,curr,op);
        if(result!=-100000){
            dfs(result,-100000,operations[i],touches+1,target);
        }
    }

    //try pressing each digit
    for(int it:working){
        if(curr==-100000){
            dfs(prev,it,op,touches+1,target);
        }
        else{
            int num=curr*10+it;
            if(curr<0) num=num*-1;
            dfs(prev,num,op,touches+1,target);
        }
    }


}

void solve(){
    cin>>n>>m>>o;
    ans=INT_MAX;
    working.resize(n);
    operations.resize(m);
    for(int i=0;i<n;i++){
        cin>>working[i];
    }
    for(int i=0;i<m;i++){
        cin>>operations[i];
    }

    int target;
    cin>>target;

    dfs(-100000,-100000,-1,0,target);

    if(ans==INT_MAX){
        cout<<-1<<endl;
    }
    else{
        cout<<ans<<endl;
    }
}


int main(){
    int t;
    cin>>t;
    for(int i=0;i<t;i++){
        solve();
    }
    return 0;
}