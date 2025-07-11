#include<bits/stdc++.h>

using namespace std;

void f( int i,int n, int p1, int p2, int & ans, vector<bool>& visited, vector<int>& v){
    //uodate ans if equal height achieved
    if(p1==p2){
        ans=max(p1,ans);
    }
    //tried all elements, so return
    if(i==n){
        return;
    }
    
    //add to first pillar
    f(i+1,n,p1+v[i],p2,ans,visited,v);
    //add to second pillar
    f(i+1,n,p1,p2+v[i],ans,visited,v);
    //add to neither 
    f(i+1,n,p1,p2,ans,visited,v);
            
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
        f(0,n,0,0,ans,visited,v);
        cout<<ans<<endl;
    }
    return 0;
}
