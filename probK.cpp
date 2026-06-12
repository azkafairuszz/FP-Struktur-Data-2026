#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    vector<vector<int>> adj(n+1);
    for (int i = 0; i < n-1; i++) {
        int x, y; cin >> x >> y;
        adj[x].push_back(y); adj[y].push_back(x);
    }
    int Q; cin >> Q;
    while (Q--) {
        int K, M; cin >> K >> M;
        vector<int> S(K), T(K);
        for (int j = 0; j < K; j++) cin >> S[j] >> T[j];
        vector<int> queries(M);
        for (int i = 0; i < M; i++) cin >> queries[i];

        vector<int> owner(n+1, -1);
        // frontier[j] = list of (node, steps_remaining) for fire j's current wave
        // Each turn for fire j: BFS expand from frontier using T[j] hops through unburned
        // We use a queue per fire: {node, hops_left}
        // To simulate correctly: at each turn for fire j, we do BFS from all frontier nodes
        // with up to T[j] additional hops through unburned nodes

        // Use vector of queues of (node, hops_left_in_this_turn)
        // Actually simpler: maintain "wavefront" per fire = set of newly claimed nodes
        // Each turn: for fire j, start BFS from all nodes claimed by j ever,
        //   but fire can only travel through unburned. Too slow.
        
        // Better: maintain per fire a deque of frontier nodes.
        // When fire j is fed: do BFS up to T[j] hops from current frontier through unburned.
        // Newly burned nodes become new frontier for next time this fire is fed.
        
        // Initialize
        for (int i = 1; i <= n; i++) owner[i] = -1;
        vector<queue<pair<int,int>>> frontier(K); // (node, hops_remaining)
        
        for (int j = 0; j < K; j++) {
            owner[S[j]] = j;
            // hops_remaining = T[j] means can still go T[j] more hops this turn
            frontier[j].push({S[j], T[j]});
        }
        
        int burned = K;
        int total = n;
        
        // Process in rounds
        int cur = 0;
        while (burned < total) {
            // feed fire cur
            int tj = T[cur];
            // BFS from frontier[cur] with hops
            // We need a fresh BFS each time fire cur is fed
            // frontier[cur] contains nodes from last time cur was fed (newly claimed)
            // Actually we need ALL boundary nodes of fire cur
            // This approach is too slow if we re-expand all.
            
            // Standard approach: maintain "active frontier" = nodes that still have
            // unburned neighbors. Each turn, expand by T[j] hops.
            // Use a local BFS queue with (node, hops_left)
            
            queue<pair<int,int>> bfs;
            while (!frontier[cur].empty()) {
                bfs.push(frontier[cur].front());
                frontier[cur].pop();
            }
            
            // BFS
            while (!bfs.empty()) {
                auto [v, hops] = bfs.front(); bfs.pop();
                if (hops == 0) continue;
                for (int u : adj[v]) {
                    if (owner[u] == -1) {
                        owner[u] = cur;
                        burned++;
                        frontier[cur].push({u, T[cur]}); // next time this fire feeds, start from u
                        bfs.push({u, hops-1});
                    }
                }
            }
            
            cur = (cur + 1) % K;
        }
        
        for (int i = 0; i < M; i++) {
            cout << owner[queries[i]] + 1;
            if (i < M-1) cout << " ";
        }
        cout << "\n";
    }
}