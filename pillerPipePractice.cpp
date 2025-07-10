#include<bits/stdc++.h>

using namespace std;

void f( int n, int p1, int p2, int & ans, vector<bool>& visited, vector<int>& v){
    if(p1==p2){
        ans=max(p1,ans);
    }

    for(int i=0;i<n;i++){
        if(visited[i]==false){
            visited[i]=true;
            f(n,p1+v[i],p2,ans,visited,v);
            f(n,p1,p2+v[i],ans,visited,v);
            visited[i]=false;
        }
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

        vector<bool> visited(n,false);
        int ans=0;
        f(n,0,0,ans,visited,v);
        cout<<ans<<endl;
    }
    return 0;
}