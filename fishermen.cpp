#include<bits/stdc++.h>

using namespace std;

vector<int> getNearest(int gate,vector<bool>& occupied, int N){
    vector<pair<int,int>> dist;
    for(int i=1;i<=N;i++){
        if(!occupied[i]){
            int distance=abs(gate-i)+1;
            dist.push_back({distance,i});
        }
    }

    sort(dist.begin(),dist.end());
    vector<int> v;
    for(auto it:dist){
        v.push_back(it.second);
    }

    return v;
}

void assignFishermen(int g_id,int fisher_ind,int currSum,int& ans, vector<int>& perm, vector<int>& gates, vector<int>& num, vector<bool>& occupied, int N){
    if(currSum>=ans) return;

    int gatePos=gates[perm[g_id]];
    int total=num[perm[g_id]];

    if(fisher_ind==total){
        if(g_id==2){
            ans=min(ans,currSum);
            return;
        }
        assignFishermen(g_id+1,0,currSum,ans,perm,gates,num,occupied,N);
        return;
    }
    vector<int> nearest=getNearest(gatePos,occupied,N);
    int minDist=abs(gatePos-nearest[0])+1;
    
    vector<int> choices;
    for(int i:nearest){
        if(abs(i-gatePos)+1==minDist){
            choices.push_back(i);
        }
        else break;
    }

    for(int i:choices){
        occupied[i]=true;
        assignFishermen(g_id,fisher_ind+1,currSum+minDist,ans,perm,gates,num,occupied,N);
        occupied[i]=false;
    }

}

int main(){
    int N;
    cin>>N;

    vector<int> gates(3),num(3);
    for(int i=0;i<3;i++) cin>>gates[i];
    for(int i=0;i<3;i++) cin>>num[i];

    vector<int> perm={0,1,2};
    int ans=INT_MAX;
    do{
        vector<bool> occupied(N+1,false);
        assignFishermen(0,0,0,ans,perm,gates,num,occupied,N);
    }while(next_permutation(perm.begin(),perm.end()));

    cout<<ans<<endl;
    return 0;
}