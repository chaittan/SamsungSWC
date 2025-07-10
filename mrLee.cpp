#include<iostream>

using namespace std;

int visited[12]={0};
void init(){
    for(int i=0;i<12;i++){
        visited[i]=0;
    }
}

int dfs(int i, int c,int n,int arr[12][12]){
    if(c==n){
        return arr[i][0]==0?1e9:arr[i][0];
        // RETURN TO STARTING CITY!!!!
        /* IMPORTANT EDGE CASE IF NO VALID PATH FROM LAST NODE TO FIRST NODE*/
    }
    int minCost=1e9;
    for(int j=0;j<n;j++){
        //IF NODE NOT VALID !!!!
        if(j==i||arr[i][j]==0) continue;
        if(!visited[j]){
            visited[j]=1;
            int cost=dfs(j,c+1,n,arr)+arr[i][j];
            minCost=min(minCost,cost);
            visited[j]=0;
        }
    }
    return minCost;
}


int main(){
    int t;
    cin>>t;
    for(int i=0;i<t;i++){
        int n;
        cin>>n;
        int arr[12][12];
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                cin>>arr[i][j];
            }
        }
        init();
        visited[0]=1;
        int ans=dfs(0,1,n,arr);
        cout<<ans<<endl;
    }
    return 0;
}