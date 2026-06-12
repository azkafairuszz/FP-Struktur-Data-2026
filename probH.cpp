#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, d_target;
vector<int> adj[2005];
int dist_mat[2005][2005];

void bfs(int src) {
    queue<int> q;
    fill(dist_mat[src]+1, dist_mat[src]+n+1, -1);
    dist_mat[src][src] = 0;
    q.push(src);
    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (int u : adj[v]) {
            if (dist_mat[src][u] == -1) {
                dist_mat[src][u] = dist_mat[src][v] + 1;
                q.push(u);
            }
        }
    }
}

ll countPairsSum(map<int,ll>& df, int target) {
    ll res = 0;
    for (auto& [dv, cv] : df) {
        int other = target - dv;
        if (other < dv) continue;
        if (!df.count(other)) continue;
        if (other == dv) res += cv*(cv-1)/2;
        else res += cv * df[other];
    }
    return res;
}

ll countTriplesSum(map<int,ll>& df, int target) {
    ll res = 0;
    vector<pair<int,ll>> dv(df.begin(), df.end());
    int m = dv.size();
    for (int i = 0; i < m; i++) {
        for (int j = i; j < m; j++) {
            int rem = target - dv[i].first - dv[j].first;
            if (rem < dv[j].first) break;
            auto it = df.find(rem);
            if (it == df.end()) continue;
            ll ci = dv[i].second, cj = dv[j].second, ck = it->second;
            if (dv[i].first == dv[j].first && dv[j].first == rem)
                res += ci*(ci-1)*(ci-2)/6;
            else if (dv[i].first == dv[j].first)
                res += ci*(ci-1)/2 * ck;
            else if (dv[j].first == rem)
                res += ci * cj*(cj-1)/2;
            else
                res += ci * cj * ck;
        }
    }
    return res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t; cin >> t;
    while (t--) {
        cin >> n >> d_target;
        for (int i = 1; i <= n; i++) adj[i].clear();
        for (int i = 0; i < n-1; i++) {
            int u, v; cin >> u >> v;
            adj[u].push_back(v); adj[v].push_back(u);
        }
        for (int i = 1; i <= n; i++) bfs(i);

        int need = d_target - 1;
        ll ans = 0;

        for (int m = 1; m <= n; m++) {
            vector<int> grp(n+1, 0);
            int gi = 1;
            queue<int> bq;
            for (int nb : adj[m]) {
                grp[nb] = gi;
                bq.push(nb);
                gi++;
            }
            while (!bq.empty()) {
                int v = bq.front(); bq.pop();
                for (int u : adj[v]) {
                    if (u != m && grp[u] == 0) {
                        grp[u] = grp[v];
                        bq.push(u);
                    }
                }
            }

            map<int,ll> freq_all;
            map<int, map<int,ll>> freq_grp;
            for (int v = 1; v <= n; v++) if (v != m) {
                freq_all[dist_mat[m][v]]++;
                freq_grp[grp[v]][dist_mat[m][v]]++;
            }

            ll tp = countPairsSum(freq_all, need);
            ll sp = 0;
            for (auto& [g, gf] : freq_grp) sp += countPairsSum(gf, need);
            ans += (tp - sp);
            ll tot_triples = countTriplesSum(freq_all, need);
            ll bad = 0;
            for (auto& [g, gf] : freq_grp) {
                // term2
                bad += countTriplesSum(gf, need);
                vector<pair<int,ll>> gv(gf.begin(), gf.end());
                int sz = gv.size();
                for (int i = 0; i < sz; i++) {
                    for (int j = i; j < sz; j++) {
                        int s = gv[i].first + gv[j].first;
                        int rem = need - s;
                        if (rem < 0) continue;
                        ll pairs;
                        if (i == j) pairs = gv[i].second*(gv[i].second-1)/2;
                        else pairs = gv[i].second * gv[j].second;
                        ll c_all = freq_all.count(rem) ? freq_all[rem] : 0;
                        ll c_in = gf.count(rem) ? gf[rem] : 0;
                        bad += pairs * (c_all - c_in);
                    }
                }
            }
            ans += (tot_triples - bad);
        }
        cout << ans << "\n";
    }
}