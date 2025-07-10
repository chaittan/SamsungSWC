/*
5
3 3
1 1 1
0 0 0
0 0 0
0 0 0 2
3 3
1 0 0
1 0 0
1 0 0
0 0 2 0
4 4
1 1 1 0
0 0 1 0
0 0 1 0
0 0 1 0
0 0 3 2
3 3
1 0 0
0 0 0
0 0 1
0 0 2 2
3 3
1 1 1
1 1 1
1 1 1
1 1 1 1

output:
0
2
3
0
0
*/



#include<bits/stdc++.h>

using namespace std;

bool isValid(int x,int y, int n, int m){
    return (x>=0&&x<n&&y>=0&&y<m);
}

int main(){
    int t;
    cin>>t;
    while(t--){
        int n,m;
        cin>>n>>m;
        vector<vector<int>> v(n,vector<int>(m,0)),dist(n,vector<int>(m,INT_MAX)),visited(n,vector<int>(m));
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                cin>>v[i][j];
            }
        }

        int sx,sy,dx,dy;
        cin>>sx>>sy>>dx>>dy;
        queue<pair<int,int>> q;
        dist[sx][sy]=0;
        visited[sx][sy]=1;
        q.push({sx,sy});
        while(!q.empty()){
            auto it=q.front();
            q.pop();
            int x=it.first,y=it.second,dis=dist[x][y];

            vector<int> dx={0,1,0,-1},dy={1,0,-1,0};
            for(int i=0;i<4;i++){
                int nx=x+dx[i],ny=y+dy[i];
                if(isValid(nx,ny,n,m)&&visited[nx][ny]==0&&v[nx][ny]==1){
                    if(i==0||i==2){
                        dist[nx][ny]=dist[x][y];                        
                    }
                    else{
                        dist[nx][ny]=dist[x][y]+1;
                    }
                    visited[nx][ny]=1;
                    q.push({nx,ny});
                }
            }
        }

        cout<<dist[dx][dy]<<endl;
        
    }   
    return 0;
}