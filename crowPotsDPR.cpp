#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const long long INF = 1e18;

// Recursive function with memoization
long long solve(int i, int potsLeft, int n, const vector<int>& arr, vector<vector<long long>>& dp) {
    if (potsLeft == 1) {
        return 1LL * (n - i) * arr[i];
    }

    if (dp[i][potsLeft] != -1)
        return dp[i][potsLeft];

    long long res = INF;

    for (int next = i + 1; next < n; ++next) {
        long long cost = solve(next, potsLeft - 1, n, arr, dp) + 1LL * (next - i) * arr[i];
        res = min(res, cost);
    }

    return dp[i][potsLeft] = res;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;

        vector<int> arr(n);
        for (int i = 0; i < n; ++i)
            cin >> arr[i];

        sort(arr.begin(), arr.end());

        // Initialize dp table with -1
        vector<vector<long long>> dp(n + 1, vector<long long>(k + 1, -1));

        long long ans = INF;

        for (int i = 0; i < n; ++i) {
            ans = min(ans, solve(i, k, n, arr, dp));
        }

        cout << ans << endl;
    }

    return 0;
}
