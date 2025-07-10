#include <bits/stdc++.h>
using namespace std;

int dp[16][16][1 << 15]; // dp[i][compDone][bitmask]
const int INF = 1e9;

void f(int i, vector<int>& mines, int minV, int maxV,
       int currSum, int compDone, int& ans, int m, int c, int bitmask) {
    
    // Base case: completed circular path
    if (bitmask & (1 << i)) {
        minV = min(currSum, minV);
        maxV = max(currSum, maxV);
        if (compDone == c - 1) {
            ans = min(ans, maxV - minV);
        }
        return;
    }

    // Invalid: too many partitions
    if (compDone >= c) return;

    if (dp[i][compDone][bitmask] != -1) return; // already visited
    dp[i][compDone][bitmask] = 1;

    int j = (i + 1) % m;

    // Option 1: continue current group
    f(j, mines, minV, maxV, currSum + mines[i], compDone, ans, m, c, bitmask | (1 << i));

    // Option 2: start new group
    int newMin = min(minV, currSum);
    int newMax = max(maxV, currSum);
    f(j, mines, newMin, newMax, mines[i], compDone + 1, ans, m, c, bitmask | (1 << i));
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

        int ans = INF;
        memset(dp, -1, sizeof(dp));

        for (int i = 0; i < m; i++) {
            f(i, mines, INT_MAX, INT_MIN, 0, 0, ans, m, c, 0);
        }

        cout << ans << endl;
    }
    return 0;
}
