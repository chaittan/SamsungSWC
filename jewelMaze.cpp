#include<bits/stdc++.h>

using namespace std;

bool isValid(int x,int y, int n){
    return (x>=0&&x<n&&y>=0&&y<n);
}

void dfs(int x,int y, int n, vector<vector<int>>& v,vector<pair<int,int>>& currentPath,vector<pair<int,int>>& bestPath,int &ans,int currJewels, vector<vector<int>>& visited){
    
    visited[x][y]=1;
    currentPath.push_back({x,y});
    if(v[x][y]==2) currJewels+=1;
    if(x==n-1&&y==n-1){
        if(currJewels>=ans){
            ans=currJewels;
            bestPath=currentPath;
        }
        currentPath.pop_back();
        visited[x][y]=0;
        return;
    }
    
    
    
    vector<int> dx={0,1,0,-1};
    vector<int> dy={1,0,-1,0};
    for(int i=0;i<4;i++){
        int nx=x+dx[i];
        int ny=y+dy[i];
        if(isValid(nx,ny,n)&&visited[nx][ny]==0&&v[nx][ny]!=1){
            dfs(nx,ny,n,v,currentPath,bestPath,ans,currJewels,visited);
        }
    }
    currentPath.pop_back();
    visited[x][y]=0;
    
}

int main(){
    int t;
    cin>>t;
    for(int i=0;i<t;i++){
        int n;
        cin>>n;
        vector<vector<int>> v(n,vector<int>(n,0));
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                cin>>v[i][j];
            }
        }

        vector<pair<int,int>> currentPath,bestPath;
        vector<vector<int>> visited(n,vector<int>(n,0));
        int ans=-1;
        

        dfs(0,0,n,v,currentPath,bestPath,ans,0,visited);
        for(auto it:bestPath){
            v[it.first][it.second]=3;
        }

        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                cout<<v[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<ans<<endl;
    }
}