#include <iostream>
#include <vector>

using namespace std;

long long ans;
int target_d;

void dfs(int u, int p, const vector<vector<int>>& adj, vector<vector<int>>& dep_counts) {
    dep_counts[u].assign(1, 1);
    for (int v : adj[u]) {
        if (v == p) continue;
        vector<vector<int>> child_deps;
        dfs(v, u, adj, child_deps);
        
        for (int i = 0; i < dep_counts[u].size(); i++) {
            for (int j = 0; j < child_deps[v].size(); j++) {
                if (i + j + 1 == target_d) {
                    ans += 1LL * dep_counts[u][i] * child_deps[v][j];
                }
            }
        }
        
        if (child_deps[v].size() + 1 > dep_counts[u].size()) {
            dep_counts[u].resize(child_deps[v].size() + 1, 0);
        }
        for (int j = 0; j < child_deps[v].size(); j++) {
            dep_counts[u][j + 1] += child_deps[v][j];
        }
    }
}

void solve() {
    int n;
    cin >> n >> target_d;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    ans = 0;
    vector<vector<int>> dep_counts(n + 1);
    dfs(1, 0, adj, dep_counts);
    
    long long total_triplets = ans * (n - 3);
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}