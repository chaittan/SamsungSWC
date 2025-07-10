#include<bits/stdc++.h>

using namespace std;

struct Node{
    int x,y,level;
    Node(int x,int y,int level): x(x),y(y),level(level){}
};

bool isValid(int x,int y,int n,int m){
    return (x>=0&&x<n&&y>=0&&y<m);
}

int main(){
    int t;
    cin>>t;
    for(int i=0;i<t;i++){
        int n,m;
        cin>>n>>m;
        vector<vector<int>> v(n,vector<int>(m,0));
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                cin>>v[i][j];
            }
        }
        int sx,sy;
        cin>>sx>>sy;
        sx--;sy--;
        v[sx][sy]=2;
        queue<Node> q;
        q.push(Node(sx,sy,1));
        int time;
        while(!q.empty()){
            Node frontN=q.front();
            q.pop();
            vector<pair<int,int>> dxy={{0,1},{1,0},{0,-1},{-1,0}};
            time=frontN.level;
            for(int i=0;i<4;i++){
                int nx=frontN.x+dxy[i].first,ny=frontN.y+dxy[i].second;
                if(isValid(nx,ny,n,m)&&v[nx][ny]==1){
                    v[nx][ny]=2;
                    q.push(Node(nx,ny,time+1));
                }
            }
        }
        cout<<"Case #"<<i+1<<endl;
        cout<<time<<endl;
    }


}