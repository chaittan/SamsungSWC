#include<iostream>
#include<queue>
#include<vector>
using namespace std;

// Define a pipe with open directions
struct pipe {
    bool left, up, right, down;
    pipe(): left(false), right(false), up(false), down(false) {}
    pipe(bool left, bool up, bool right, bool down): left(left), up(up), right(right), down(down) {}
};


pipe mapp[1000][1000];

// Node for BFS traversal NO NEED TO STORE PIPE INFO !!!
struct bfsNode {
    int r, c, level;
    bfsNode(int r, int c, int level): r(r), c(c), level(level) {}
};

int bfs(int r, int c, int l, int m, int n) {
    // VERY VERY IMPORTANT TEST CASE
    if (mapp[r][c].left == false && mapp[r][c].right == false &&
        mapp[r][c].up == false && mapp[r][c].down == false)
        return 0;

    queue<bfsNode> q;
    // THE QUEUE SHOULD NOT BE POINTER TO BFSNODE , STORE BY VALUE OTHERWISE MEMORY LEAK !!!
    vector<vector<int>> visited(m, vector<int>(n, 0));

    visited[r][c] = 1;
    q.push(bfsNode(r, c, 1));  // ✅ Start level is 1, not 0 (since cell is immediately reachable)

    while (!q.empty()) {
        bfsNode frontN = q.front();
        q.pop();

        int cr = frontN.r, cc = frontN.c, level = frontN.level;
        pipe info = mapp[cr][cc];

        if (level + 1 > l) continue;  // ✅ Do not explore beyond allowed time limit

        // ✅ Directional checks — ensure both current and target cells have open ends
        // 🔁 Can travel only if both ends of connected pipe are open

        // ONLY ADD TO THE QUEUE IF NOT VISITED !!!!!!! VERY VERY IMPORTANT 
        // Move Left 
        if (cc - 1 >= 0 && !visited[cr][cc - 1] && info.left && mapp[cr][cc - 1].right) {
            visited[cr][cc - 1] = 1;
            q.push(bfsNode(cr, cc - 1, level + 1));
        }

        // Move Right
        if (cc + 1 < n && !visited[cr][cc + 1] && info.right && mapp[cr][cc + 1].left) {
            visited[cr][cc + 1] = 1;
            q.push(bfsNode(cr, cc + 1, level + 1));
        }

        // Move Up
        if (cr - 1 >= 0 && !visited[cr - 1][cc] && info.up && mapp[cr - 1][cc].down) {
            visited[cr - 1][cc] = 1;
            q.push(bfsNode(cr - 1, cc, level + 1));
        }

        // Move Down
        if (cr + 1 < m && !visited[cr + 1][cc] && info.down && mapp[cr + 1][cc].up) {
            visited[cr + 1][cc] = 1;
            q.push(bfsNode(cr + 1, cc, level + 1));
        }
    }

    // ✅ Count all visited cells
    int count = 0;
    for (int i = 0; i < m; i++)     // ✔️ Correct matrix size used here
        for (int j = 0; j < n; j++)
            if (visited[i][j]) count++;

    return count;
}

int main() {
    int tests;
    cin >> tests;
    while (tests--) {
        int n, m, r, c, l;
        cin >> n >> m >> r >> c >> l;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int type;
                cin >> type;

                // ✅ Reset the pipe before assigning
                mapp[i][j] = pipe();

                // 🔁 Correct pipe connection mapping
                switch (type) {
                    case 1: mapp[i][j] = pipe(true, true, true, true); break;       // All sides open
                    case 2: mapp[i][j] = pipe(false, true, false, true); break;     // Up & Down
                    case 3: mapp[i][j] = pipe(true, false, true, false); break;     // Left & Right
                    case 4: mapp[i][j] = pipe(false, true, true, false); break;     // Up & Right
                    case 5: mapp[i][j] = pipe(false, false, true, true); break;     // Right & Down
                    case 6: mapp[i][j] = pipe(true, false, false, true); break;     // Left & Down
                    case 7: mapp[i][j] = pipe(true, true, false, false); break;     // Left & Up
                    // 🔁 You missed `case 0:` which represents a blocked cell (can be skipped since pipe() already initializes all false)
                }
            }
        }

        // ✅ Start BFS with proper params (r, c, l, rows, cols)
        cout << bfs(r, c, l, n, m) << endl;
    }

    return 0;
}
