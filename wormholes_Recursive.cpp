#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

struct Node {
    int x, y;
    Node(int x, int y) : x(x), y(y) {}
};

int manhattanDistance(Node* a, Node* b) {
    return abs(a->x - b->x) + abs(a->y - b->y);
}

void dfs(Node* current, Node* destination, Node* points[], int visited[], int currentCost, int& minCost, int n, int cost[14][14]) {
    // Try going directly to destination from current point
    minCost = min(minCost, currentCost + manhattanDistance(current, destination));

    for (int i = 0; i < n; i++) {
        int entry = 2 * i + 1;
        int exit = 2 * i + 2;

        if (!visited[entry] && !visited[exit]) {
            visited[entry] = visited[exit] = 1;

            // Try entering from entry point and exiting from exit point
            dfs(points[exit], destination, points, visited,
                currentCost + cost[entry][exit] + manhattanDistance(current, points[entry]),
                minCost, n, cost);

            // Try entering from exit point and exiting from entry point
            dfs(points[entry], destination, points, visited,
                currentCost + cost[entry][exit] + manhattanDistance(current, points[exit]),
                minCost, n, cost);

            visited[entry] = visited[exit] = 0;
        }
    }
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        const int MAX_POINTS = 2 * n + 2;
        Node* points[MAX_POINTS];
        int cost[14][14];

        // Initialize cost matrix
        for (int i = 0; i < MAX_POINTS; i++) {
            for (int j = 0; j < MAX_POINTS; j++) {
                cost[i][j] = -1;
            }
        }

        // Read source and destination
        int sx, sy, dx, dy;
        cin >> sx >> sy >> dx >> dy;
        points[0] = new Node(sx, sy);
        points[MAX_POINTS - 1] = new Node(dx, dy);

        // Read wormholes
        for (int i = 0; i < n; i++) {
            int x1, y1, x2, y2, wCost;
            cin >> x1 >> y1 >> x2 >> y2 >> wCost;

            points[2 * i + 1] = new Node(x1, y1);
            points[2 * i + 2] = new Node(x2, y2);
            cost[2 * i + 1][2 * i + 2] = cost[2 * i + 2][2 * i + 1] = wCost;
        }

        // Fill rest of cost matrix with Manhattan distances
        for (int i = 0; i < MAX_POINTS; i++) {
            for (int j = 0; j < MAX_POINTS; j++) {
                if (cost[i][j] == -1) {
                    cost[i][j] = manhattanDistance(points[i], points[j]);
                }
            }
        }

        int visited[MAX_POINTS] = {0};
        int minCost = INT_MAX;

        dfs(points[0], points[MAX_POINTS - 1], points, visited, 0, minCost, n, cost);
        cout << minCost << endl;

        // Free memory
        for (int i = 0; i < MAX_POINTS; i++) {
            delete points[i];
        }
    }

    return 0;
}
