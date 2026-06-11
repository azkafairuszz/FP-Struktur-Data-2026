#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void dfs(int u, int p, const vector<vector<int>>& adj, vector<int>& depth, vector<vector<int>>& up) {
    up[u][0] = p;
    for (int i = 1; i < 20; i++) {
        up[u][i] = up[up[u][i - 1]][i - 1];
    }
    for (int v : adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs(v, u, adj, depth, up);
        }
    }
}

int lca(int u, int v, const vector<int>& depth, const vector<vector<int>>& up) {
    if (depth[u] < depth[v]) swap(u, v);
    
    for (int i = 19; i >= 0; i--) {
        if (depth[u] - (1 << i) >= depth[v]) {
            u = up[u][i];
        }
    }
    
    if (u == v) return u;
    
    for (int i = 19; i >= 0; i--) {
        if (up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    }
    return up[u][0];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    vector<vector<int>> adj(n + 1);
    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        adj[p].push_back(i);
        adj[i].push_back(p);
    }

    vector<int> depth(n + 1, 0);
    vector<vector<int>> up(n + 1, vector<int>(20, 1));

    dfs(1, 1, adj, depth, up);

    while (q--) {
        int a, b;
        cin >> a >> b;
        cout << lca(a, b, depth, up) << "\n";
    }

    return 0;
}