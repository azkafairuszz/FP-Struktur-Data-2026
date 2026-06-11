#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

void getInorderPositions(int u, int n, vector<int>& order) {
    if (u > n) return;
    getInorderPositions(2 * u, n, order);
    order.push_back(u);
    getInorderPositions(2 * u + 1, n, order);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());

    vector<int> inorderPos;
    getInorderPositions(1, n, inorderPos);

    vector<int> valToPos(n + 1);
    vector<int> treeNodeValue(n + 1);
    for (int i = 0; i < n; i++) {
        int pos = inorderPos[i];
        treeNodeValue[pos] = a[i];
    }

    vector<pair<int, int>> sortedNodes(n);
    for (int i = 1; i <= n; i++) {
        sortedNodes[i - 1] = {treeNodeValue[i], i};
    }
    sort(sortedNodes.begin(), sortedNodes.end());

    vector<int> parentOfVal(n);
    for (int i = 0; i < n; i++) {
        int pos = sortedNodes[i].second;
        if (pos == 1) {
            parentOfVal[i] = -1;
        } else {
            int pPos = pos / 2;
            parentOfVal[i] = treeNodeValue[pPos];
        }
    }

    for (int i = 0; i < n; i++) {
        cout << parentOfVal[i] << (i == n - 1 ? "" : " ");
    }
    cout << "\n";

    return 0;
}