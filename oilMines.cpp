#include <bits/stdc++.h>
using namespace std;

void f(int i, vector<int>& mines, vector<bool>& visited, int minV, int maxV,
       int currSum, int compDone, int& ans, int m, int c) {
    
    // Base case: if we come back to visited node (cycle complete)
    if (visited[i]) {
        minV = min(currSum, minV);
        maxV = max(currSum, maxV);
        if (compDone == c - 1) {
            ans = min(ans, maxV - minV);
        }
        return;
    }

    // Invalid case: made too many partitions
    if (compDone >= c)
        return;

    visited[i] = true;
    int j = (i + 1) % m;

    // Option 1: continue adding to current partition
    f(j, mines, visited, minV, maxV, currSum + mines[i], compDone, ans, m, c);

    // Option 2: start a new partition
    minV = min(minV, currSum);
    maxV = max(maxV, currSum);
    f(j, mines, visited, minV, maxV, mines[i], compDone + 1, ans, m, c);

    visited[i] = false; // backtrack
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int c, m;
        cin >> c >> m;
        vector<int> mines(m);
        for (int i = 0; i < m; i++) {
            cin >> mines[i];
        }

        if (c > m) {
            cout << -1 << endl;
            continue;
        }

        int ans = INT_MAX;
        vector<bool> visited(m, false);

        for (int i = 0; i < m; i++) {
            f(i, mines, visited, INT_MAX, INT_MIN, 0, 0, ans, m, c);
        }

        cout << ans << endl;
    }
    return 0;
}
