#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void solveScenario(int n, const vector<vector<int>>& adj) {
    int m;
    cin >> m;
    vector<pair<int, int>> rifts(m);
    for (int i = 0; i < m; i++) {
        cin >> rifts[i].first >> rifts[i].second;
    }

    int k;
    cin >> k;
    vector<int> critical(k);
    for (int i = 0; i < k; i++) {
        cin >> critical[i];
    }

    vector<int> dist(n + 1, 1e9);
    vector<int> owner(n + 1, 1e9);
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;

    for (int i = 0; i < m; i++) {
        int room = rifts[i].first;
        int t_start = rifts[i].second;
        pq.push({t_start, {i + 1, room}});
    }

    while (!pq.empty()) {
        auto top = pq.top();
        pq.pop();
        int d = top.first;
        int id = top.second.first;
        int u = top.second.second;

        if (d > dist[u]) continue;
        if (d == dist[u] && id >= owner[u]) continue;

        dist[u] = d;
        owner[u] = id;

        for (int v : adj[u]) {
            if (d + 1 < dist[v] || (d + 1 == dist[v] && id < owner[v])) {
                dist[v] = d + 1;
                owner[v] = id;
                pq.push({d + 1, {id, v}});
            }
        }
    }

    for (int i = 0; i < k; i++) {
        cout << owner[critical[i]] << (i == k - 1 ? "" : " ");
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int q;
    if (cin >> q) {
        while (q--) {
            solveScenario(n, adj);
        }
    }

    return 0;
}