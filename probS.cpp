#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct NodeResult {
    long long take;
    long long skip;
};

NodeResult solveTree(int idx, int n, const vector<long long>& a) {
    if (idx > n || a[idx] == -1) {
        return {0, 0};
    }

    NodeResult leftNode = solveTree(2 * idx, n, a);
    NodeResult rightNode = solveTree(2 * idx + 1, n, a);

    long long takeCurrent = a[idx] + leftNode.skip + rightNode.skip;
    long long skipCurrent = max(leftNode.take, leftNode.skip) + max(rightNode.take, rightNode.skip);

    return {takeCurrent, skipCurrent};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<long long> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    NodeResult result = solveTree(1, n, a);
    cout << max(result.take, result.skip) << "\n";

    return 0;
}