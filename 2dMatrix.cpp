/*
4
3
1 2 3
4 5 6
7 8 9
4
1 x 2 3
4 5 x 6
7 8 9 1
2 3 4 5
3
0 x 1
x x x
2 2 2
3
1 1 1
1 1 1
1 1 1


OUTPUT:
19 1
32 1
0 0
3 6
*/

#include <bits/stdc++.h>
using namespace std;

// Recursion with memoization, no globals:
// dfs returns {bestSum, countPaths} from (i,j) to (n-1,n-1).

pair<long long,long long> dfs(
    int i, int j,
    int n,
    const vector<string>& grid,
    vector<vector<long long>>& memoSum,
    vector<vector<long long>>& memoCnt,
    vector<vector<bool>>& seen
) {
    // Boundary or obstacle
    if (i < 0 || i >= n || j < 0 || j >= n || grid[i][j] == 'x')
        return {LLONG_MIN, 0};
    // Destination
    if (i == n-1 && j == n-1)
        return {0, 1};

    if (seen[i][j])
        return {memoSum[i][j], memoCnt[i][j]};
    seen[i][j] = true;

    static const int di[3] = {0,1,1};
    static const int dj[3] = {1,1,0};

    long long best = LLONG_MIN;
    long long ways = 0;
    for (int d = 0; d < 3; ++d) {
        int ni = i + di[d];
        int nj = j + dj[d];
        auto [s, c] = dfs(ni, nj, n, grid, memoSum, memoCnt, seen);
        if (s == LLONG_MIN) continue;
        if (s > best) {
            best = s;
            ways = c;
        } else if (s == best) {
            ways += c;
        }
    }

    if (best == LLONG_MIN) {
        memoSum[i][j] = LLONG_MIN;
        memoCnt[i][j] = 0;
    } else {
        memoSum[i][j] = best + (grid[i][j] - '0');
        memoCnt[i][j] = ways;
    }
    return {memoSum[i][j], memoCnt[i][j]};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<string> grid(n);
        for (int i = 0; i < n; ++i) {
            grid[i].resize(n);
            for (int j = 0; j < n; ++j)
                cin >> grid[i][j];
        }
        // Force start/end to zero
        grid[0][0] = '0';
        grid[n-1][n-1] = '0';

        vector<vector<long long>> memoSum(n, vector<long long>(n));
        vector<vector<long long>> memoCnt(n, vector<long long>(n));
        vector<vector<bool>> seen(n, vector<bool>(n, false));

        auto [bestSum, countPaths] = dfs(
            0, 0, n,
            grid, memoSum, memoCnt, seen
        );

        if (bestSum == LLONG_MIN || countPaths == 0)
            cout << "0 0\n";
        else
            cout << bestSum << " " << countPaths << "\n";
    }
    return 0;
}
