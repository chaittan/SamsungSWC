#include<iostream>
#include<queue>
#include<bits/stdc++.h>

using namespace std;

struct pipe{
    bool left,up,right,down;
    pipe(): left(false),right(false),up(false), down(false){}
    pipe(bool left,bool up, bool right, bool down): left(left),up(up),right(right),down(down){}
};

pipe mapp[1000][1000];

struct bfsNode{
    int r,c,level;
    pipe info;
    bfsNode(int r,int c,int level,pipe info): r(r),c(c),level(level),info(info){}
};


int bfs(int r,int c, int l,int m, int n){
    queue<bfsNode*> q;
    vector<vector<int>> visited(m,vector<int>(n,0));

    visited[r][c]=1;
    bfsNode* root=new bfsNode(r,c,1,mapp[r][c]);
    q.push(root);

    while(!q.empty()){
        bfsNode* frontN=q.front();
        q.pop();
        int r=frontN->r,c=frontN->c,level=frontN->level;
        pipe info=frontN->info;
        if(frontN->level+1<=l){
            if(c-1>=0&&info.left==true&&mapp[r][c-1].right==true){
                visited[r][c-1]=1;
                bfsNode* root=new bfsNode(r,c-1,level+1,mapp[r][c-1]);
                q.push(root);
            }
            if(c+1<n&&info.right==true&&mapp[r][c+1].left==true){
                visited[r][c+1]=1;
                bfsNode* root=new bfsNode(r,c+1,level+1,mapp[r][c+1]);
                q.push(root);
            }
            if(r-1>=0&&info.up==true&&mapp[r-1][c].down==true){
                visited[r-1][c]=1;
                bfsNode* root=new bfsNode(r-1,c,level+1,mapp[r-1][c]);
                q.push(root);
            }
            if(r+1<m&&info.down==true&&mapp[r+1][c].up==true){
                visited[r+1][c]=1;
                bfsNode* root=new bfsNode(r+1,c,level+1,mapp[r+1][c]);
                q.push(root);
            }
        }
    }

    int count=0;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(visited[i][j]==1) count++;
        }
    }

    return count;
}


int main(){
    int tests;
    cin>>tests;
    for(int t=1;t<=tests;t++){
        int n,m,r,c,l;
        cin>>n>>m>>r>>c>>l;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                int type;
                cin>>type;
                if(type==0){
                    mapp[i][j].left=false;
                    mapp[i][j].right=false;
                    mapp[i][j].up=false;
                    mapp[i][j].down=false;
                }
                else if(type==1){
                    mapp[i][j].left=true;
                    mapp[i][j].right=true;
                    mapp[i][j].up=true;
                    mapp[i][j].down=true;
                }
                else if(type==2){
                    mapp[i][j].left=false;
                    mapp[i][j].right=false;
                    mapp[i][j].up=true;
                    mapp[i][j].down=true;
                }
                else if(type==3){
                    mapp[i][j].left=true;
                    mapp[i][j].right=true;
                    mapp[i][j].up=false;
                    mapp[i][j].down=false;
                }
                else if(type==4){
                    mapp[i][j].left=false;
                    mapp[i][j].right=true;
                    mapp[i][j].up=true;
                    mapp[i][j].down=false;
                }
                else if(type==5){
                    mapp[i][j].left=false;
                    mapp[i][j].right=true;
                    mapp[i][j].up=false;
                    mapp[i][j].down=true;
                }
                else if(type==6){
                    mapp[i][j].left=true;
                    mapp[i][j].right=false;
                    mapp[i][j].up=false;
                    mapp[i][j].down=true;
                }
                else if(type==7){
                    mapp[i][j].left=true;
                    mapp[i][j].right=false;
                    mapp[i][j].up=true;
                    mapp[i][j].down=false;
                }
            }
        }

        int ans=bfs(r,c,l,n,m);
        cout<<ans<<endl;
    }
    return 0;
}