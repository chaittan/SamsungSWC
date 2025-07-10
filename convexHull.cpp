#include<bits/stdc++.h>

class Solution {
    int crossProduct(vector<int>& a, vector<int>& b,vector<int>& c){
        // x2-x1*y3-y1 - x3-x1*y2-y1
        return (b[0]-a[0])*(c[1]-a[1])-(c[0]-a[0])*(b[1]-a[1]);
    }
public:
    vector<vector<int>> outerTrees(vector<vector<int>>& trees) {
        if(trees.size()<=3){
            return trees;
        }

        vector<vector<int>> upperHull,lowerHull;
        int n=trees.size();
        sort(trees.begin(),trees.end());
        upperHull.push_back(trees[0]);
        upperHull.push_back(trees[1]);

        for(int i=2;i<n;i++){
            int us=upperHull.size();
            while(upperHull.size()>=2&&crossProduct(upperHull[us-2],upperHull[us-1],trees[i])>0){
                upperHull.pop_back();
                us--;
            }
            upperHull.push_back(trees[i]);
        }
        lowerHull.push_back(trees[n-1]);
        lowerHull.push_back(trees[n-2]);

        for(int i=n-3;i>=0;i--){
            int ls=lowerHull.size();
            while(lowerHull.size()>=2&&crossProduct(lowerHull[ls-2],lowerHull[ls-1],trees[i])>0){
                lowerHull.pop_back();
                ls--;
            }
            lowerHull.push_back(trees[i]);
        }

        set<vector<int>> st;
        for(auto it:upperHull){
            st.insert(it);
        }
        for(auto it:lowerHull){
            st.insert(it);
        }

        vector<vector<int>> ans(st.begin(),st.end());
        return ans;

    }
};