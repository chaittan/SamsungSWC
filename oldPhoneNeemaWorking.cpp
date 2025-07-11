#include <iostream>
#include <bits/stdc++.h>
using namespace std;
using ll = long long;  // Alias for long long (unused here but available)

// Global parameters:
int n, m, o;              // n: number of working digit keys
                           // m: number of working operations
                           // o: maximum number of touches allowed

vector<int> nums, ops;    // nums: list of working digits (0–9)
                           // ops:  list of working operations (1=+, 2=-, 3=*, 4=/)

int ans = INT_MAX;         // Stores the minimum touches found (initialized to "infinite")
int cnt = 1;               // Case counter (used for debug prints)

// Applies the pending operation `op` to `prev` and `curr`.
// Special sentinel values:
//   prev == -1e5 : no previous value yet → just return `curr`.
//   returns -1e9 on any invalid operation (division by zero or unknown code).
int eval(int prev, int curr, int op) {
    if (prev == -100000) {
        // No previous operand: the result is simply the current number
        return curr;
    }

    switch (op) {
        case 1:  // addition
            return prev + curr;
        case 2:  // subtraction
            return prev - curr;
        case 3:  // multiplication
            return prev * curr;
        case 4:  // division
            if (curr != 0)
                return prev / curr;
            // Division by zero detected: mark invalid
            return -1000000000;
        default:
            // Unknown operation code: mark invalid
            return -1000000000;
    }
}

// Recursive DFS to explore all sequences of digit-presses and operations.
// Params:
//   prev    = last computed/copied value (or -1e5 if none yet)
//   curr    = current number being typed (or -1e5 if none yet)
//   op      = pending operation code to apply when pressing '='
//   touches = number of key-presses used so far
//   target  = the integer value we want to reach
void cal(int prev, int curr, int op, int touches, int target) {
    // 1) Prune if we've already exceeded the best known answer or max touches
    if (touches > ans || touches > o)
        return;

    // 2) "Press '='" scenario: if we have both curr and a pending op
    if (curr != -100000 && op != -1) {
        // Skip illegal divide-by-zero
        if (!(curr == 0 && op == 4)) {
            int res = eval(prev, curr, op);
            if (res == target) {
                // +1 touch for pressing '='
                ans = min(ans, touches + 1);
            }
        }
    }

    // 3) Direct match scenarios (no pending operation):
    //    a) Typed the target fully into `curr`
    if (curr == target && prev == -100000 && op == -1) {
        ans = min(ans, touches);
    }
    //    b) Copied a result into `prev` that equals the target
    if (prev == target && curr == -100000 && op == -1) {
        ans = min(ans, touches);
    }

    // 4) Try pressing each available operation key
    for (int i = 0; i < m; i++) {
        // Can't operate if there's no current number
        if (curr == -100000) break;
        // Guard against performing x / 0 next
        if (curr == 0 && op == 4) break;

        int result = eval(prev, curr, op);
        if (result != -1000000000) {
            // Commit the current number into `prev`, reset `curr`, set new op
            cal(result, -100000, ops[i], touches + 1, target);
        }
    }

    // 5) Try pressing each available digit key
    for (int d : nums) {
        if (curr == -100000) {
            // Start typing a new number
            cal(prev, d, op, touches + 1, target);
        } else {
            // Append digit: e.g. 12 -> 123
            int t = abs(curr) * 10 + d;
            if (curr < 0) t = -t;  // preserve sign
            cal(prev, t, op, touches + 1, target);
        }
    }
}

// Handles a single test case: reads input, runs the search, prints result.
void solve() {
    cin >> n >> m >> o;
    ans = INT_MAX;

    nums.resize(n);
    ops .resize(m);
    for (int i = 0; i < n; i++) cin >> nums[i];
    for (int i = 0; i < m; i++) cin >> ops[i];

    int target;
    cin >> target;

    // Debug line: show the target for this test case
    cout << "I have entered target = " << target << endl;

    // Start the DFS with no values and zero touches
    cal(-100000, -100000, -1, 0, target);

    // If ans was never updated, it's impossible within the touch limit
    if (ans == INT_MAX)
        cout << -1 << "\n";
    else
        cout << ans << "\n";

    cnt++;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
