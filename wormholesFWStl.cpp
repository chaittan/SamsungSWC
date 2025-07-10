#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int manhattanDistance(pair<int, int> &a, pair<int, int> &b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        int total = 2 * n + 2;
        vector<pair<int, int>> points(total);
        vector<vector<int>> cost(total, vector<int>(total, -1));

        int sx, sy, tx, ty;
        cin >> sx >> sy >> tx >> ty;
        points[0] = {sx, sy};
        points[total - 1] = {tx, ty};

        for (int i = 0; i < n; ++i) {
            int x1, y1, x2, y2, value;
            cin >> x1 >> y1 >> x2 >> y2 >> value;
            points[2 * i + 1] = {x1, y1};
            points[2 * i + 2] = {x2, y2};
            cost[2 * i + 1][2 * i + 2] = value;
            cost[2 * i + 2][2 * i + 1] = value;
        }

        for (int i = 0; i < total; ++i) {
            for (int j = 0; j < total; ++j) {
                if (cost[i][j] == -1) {
                    cost[i][j] = manhattanDistance(points[i], points[j]);
                }
            }
        }

        // // Floyd-Warshall
        // for (int k = 0; k < total; ++k) {
        //     for (int i = 0; i < total; ++i) {
        //         for (int j = 0; j < total; ++j) {
        //             if (i == j || i == k || j == k) continue;
        //             cost[i][j] = min(cost[i][j], cost[i][k] + cost[k][j]);
        //         }
        //     }
        // }

        for(int k=0;k<total;k++){
            for(int i=0;i<total;i++){
                for(int j=0;j<total;j++){
                    cost[i][j]=min(cost[i][j],cost[i][k]+cost[k][j]);
                }
            }
        }

        cout << cost[0][total - 1] << '\n';
    }

    return 0;
}
