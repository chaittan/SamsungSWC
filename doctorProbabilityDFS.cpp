#include <bits/stdc++.h>
using namespace std;

struct Node {
    int node;
    float prob;
    int time;
    Node(int node, float prob, int time) : node(node), prob(prob), time(time) {}
};

void dfs(int i,int time,float prob,vector<vector<pair<int, float>>> &adj,vector<float>& probAtNode ){
    if(time==0){
        probAtNode[i]+=prob;
        return;
    }

    if(adj[i].empty()){
        if(time==10){
            probAtNode[i]+=prob;
        }
        return;
    }

    for(auto it:adj[i]){
        dfs(it.first,time-10,prob*it.second,adj,probAtNode);
    }
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, e, treq;
        cin >> n >> e >> treq;

        vector<vector<pair<int, float>>> adj(n); // Store float probability
        for (int i = 0; i < e; i++) {
            int x, y;
            float p;
            cin >> x >> y >> p;
            adj[x - 1].push_back({y - 1, p});
        }

        vector<float> probAtNode(n, 0.0);  // Probabilities at each node at time = treq
        
        dfs(0,treq,1.0,adj,probAtNode);

        // Find the node with the highest probability
        float maxProb = -1.0;
        int nodeAns = -1;
        for (int i = 0; i < n; i++) {
            if (probAtNode[i] > maxProb) {
                maxProb = probAtNode[i];
                nodeAns = i;
            }
        }

        cout << (nodeAns + 1) << " " << fixed << setprecision(6) << maxProb << endl;
    }
    return 0;
}
