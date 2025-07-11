#include <iostream>
#include <vector>
#include <string>

#include <cctype>
#include <algorithm>
using namespace std;

int main() {
    int K;
    string treeStr;
    cin >> K;
    cin >> treeStr;

    vector<pair<int, int>> nodes;  // {level, value}
    int level = 0;
    int i = 0;

    while (i < treeStr.length()) {
        char ch = treeStr[i];

        if (ch == '(') {
            level++;
            i++;
        } else if (ch == ')') {
            level--;
            i++;
        } else if (isdigit(ch) || ch == '-') {
            int start = i;
            while (i < treeStr.length() && (isdigit(treeStr[i]) || treeStr[i] == '-')) {
                i++;
            }
            int value = stoi(treeStr.substr(start, i - start));
            nodes.push_back(make_pair(level, value));
        } else {
            i++;
        }
    }

    int sum = 0;
    for (const auto& p : nodes) {
        int lvl = p.first;
        int val = p.second;
        if (lvl == K + 1)
            sum += val;
    }

    cout << sum << endl;
    return 0;
}
