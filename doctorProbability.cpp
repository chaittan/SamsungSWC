#include <bits/stdc++.h>
using namespace std;

struct Node {
    int node;
    float prob;
    int time;
    Node(int node, float prob, int time) : node(node), prob(prob), time(time) {}
};

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

        queue<Node> q;
        q.push(Node(0, 1.0, 0));  // Start at node 0 (1-based indexing used in input)

        vector<float> probAtNode(n, 0.0);  // Probabilities at each node at time = treq
        while (!q.empty()) {
            Node frontN = q.front();
            q.pop();
            if (frontN.time == treq) {
                probAtNode[frontN.node] += frontN.prob;
                continue;
            }

            // If the node has no outgoing edges, doctor leaves after 10 minutes
            if (adj[frontN.node].empty()) {
                if (frontN.time + 10 == treq)
                    probAtNode[frontN.node] += frontN.prob;
                continue;
            }

            for (auto &it : adj[frontN.node]) {
                q.push(Node(it.first, frontN.prob * it.second, frontN.time + 10));
            }
        }
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
