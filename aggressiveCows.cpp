#include<bits/stdc++.h>
using namespace std;
class Solution {
    bool isValid(int mid, vector<int>& stalls, int k) {
        int lastCow = stalls[0];
        int cowPlaced = 1;
        int n = stalls.size();
        for (int i = 1; i < n; i++) {
            if ((stalls[i] - lastCow) >= mid) {
                lastCow = stalls[i];
                cowPlaced++;
            }
        }
        return cowPlaced >= k;
    }

public:
    int aggressiveCows(vector<int>& stalls, int k) {
        sort(stalls.begin(), stalls.end());

        int n = stalls.size();
        int low = 1;
        int high = stalls[n - 1] - stalls[0];
        int ans = 0;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (isValid(mid, stalls, k)) {
                ans = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return ans;
    }
};
