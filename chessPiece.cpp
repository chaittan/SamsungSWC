/*
Input 
2
9 9
3 5 2 8
20 20
2 3 7 9

Output
Case #1
2
Case #2
5 
*/

#include<bits/stdc++.h>

using namespace std;

bool isValid(int x,int y, int n, int m){
    return (x>=0&&x<n&&y>=0&&y<m);
}

int main(){
    int t;
    cin>>t;
    for(int i=0;i<t;i++){
        int n,m,sx,sy,tx,ty;
        cin>>n>>m>>sx>>sy>>tx>>ty;
        sx--;sy--;tx--;ty--;
        
        queue<pair<pair<int,int>,int>> q;
        q.push({{sx,sy},0});
        vector<vector<int>> visited(n,vector<int>(m));
        visited[sx][sy]=1;
        int ans=-1;
        while(!q.empty()){
            auto it=q.front();
            int x=it.first.first;
            int y=it.first.second;
            int level=it.second;
            q.pop();
            if(x==tx&&y==ty){
                ans=level;
                break;
            }
            vector<pair<int,int>> moves={{-2,1},{-1,2},{1,2},{2,1},{2,-1},{1,-2},{-1,-2},{-2,-1}};
            for(auto itr:moves){
                int nx=x+itr.first;
                int ny=y+itr.second;
                if(isValid(nx,ny,n,m)){
                    q.push({{nx,ny},level+1});
                }
            }
        }

        cout<<ans<<endl;
    }
}