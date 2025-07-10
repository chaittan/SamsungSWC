#include<iostream>
#include<vector>

using namespace std;

int bx,by,tx,ty;
int mincount=2;
int maxSide=-1;

void init(){
    mincount=2;
    maxSide=-1;
}
bool isValid(int k,vector<vector<int>>& plot, vector<vector<int>>& prefix,int m,int n){
    bool possible=false;
    for(int i=0;i<m-k+1;i++){
        for(int j=0;j<n-k+1;j++){
            int count=prefix[i+k-1][j+k-1];
            if(j-1>=0) count-=prefix[i+k-1][j-1];
            if(i-1>=0) count-=prefix[i-1][j+k-1];
            if(i-1>=0&&j-1>=0) count+=prefix[i-1][j-1];

            if(count<=1){
                possible=true;
                if(k>maxSide){
                    bx=i+k;
                    by=j+1;
                    tx=i+1;
                    ty=j+k;
                    mincount=count;
                }
                else if(k==maxSide){
                    if(count<mincount){
                        bx=i+k;
                        by=j+1;
                        tx=i+1;
                        ty=j+k;
                        mincount=count;
                    }
                }
            }
        }
    }
    return possible;
}

int main(){
    int t;
    cin>>t;
    for(int i=0;i<t;i++){
        init();
        int m,n,k;
        cin>>m>>n>>k;
        vector<vector<int>> plot(m,vector<int>(n));
        for(int i=0;i<k;i++){
            int x,y;
            cin>>x>>y;
            plot[x-1][y-1]=1;
        }
        vector<vector<int>> prefix(m,vector<int>(n));
        for(int i=0;i<m;i++){
            prefix[i][0]=plot[i][0];
        }
        for(int i=0;i<n;i++){
            prefix[0][i]=plot[0][i];
        }
        for(int i=1;i<m;i++){
            for(int j=1;j<n;j++){
                prefix[i][j]=prefix[i][j-1]+prefix[i-1][j]+plot[i][j]-prefix[i-1][j-1];
            }
        }

        int l=1,r=min(m,n),mid;

        while(l<=r){
            mid=(l+r)/2;
            if(isValid(mid,plot,prefix,m,n)){
                l=mid+1;
            }
            else{
                r=mid-1;
            }
        }
        cout<<"# "<<i+1<<" "<<bx<<" "<<by<<" "<<tx<<" "<<ty<<" "<<endl;
    }
    return 0;
}