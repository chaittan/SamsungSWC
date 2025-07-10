#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <climits>

using namespace std;

void dfs(int u, vector<vector<int>>& adj, vector<bool>& visited, vector<bool>& recStack,
         vector<int>& path, set<vector<int>>& all_cycles) {

    visited[u] = true;
    recStack[u] = true;
    path.push_back(u);

    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs(v, adj, visited, recStack, path, all_cycles);
        }
        else if (recStack[v]) {
            // Found a cycle
            vector<int> cycle;
            bool inCycle = false;
            for (int node : path) {
                if (node == v) inCycle = true;
                if (inCycle) cycle.push_back(node);
            }
            sort(cycle.begin(), cycle.end());
            all_cycles.insert(cycle);
        }
    }

    recStack[u] = false;
    path.pop_back();
}

int main() {
    int N, M;
    cin >> N >> M;

    vector<vector<int>> adj(N + 1);
    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    set<vector<int>> all_cycles;

    for (int i = 1; i <= N; ++i) {
        vector<bool> visited(N + 1, false);
        vector<bool> recStack(N + 1, false);
        vector<int> path;
        dfs(i, adj, visited, recStack, path, all_cycles);
    }

    if (all_cycles.empty()) {
        cout << "No cycle" << endl;
        return 0;
    }

    vector<int> result;
    int minSum = INT_MAX;

    for (const auto& cycle : all_cycles) {
        int sum = 0;
        for (int node : cycle) sum += node;

        if (sum < minSum || (sum == minSum && cycle < result)) {
            minSum = sum;
            result = cycle;
        }
    }

    for (int node : result) {
        cout << node << " ";
    }
    cout << endl;

    return 0;
}
