#include <bits/stdc++.h>
using namespace std;

struct SegTree {
    int n;
    vector<int> st;

    SegTree(int n) : n(n), st(4 * n + 4, -1) {}

    void update(int p, int l, int r, int idx, int val) {
        if (l == r) {
            st[p] = val;
            return;
        }
        int m = (l + r) >> 1;
        if (idx <= m) update(p << 1, l, m, idx, val);
        else update(p << 1 | 1, m + 1, r, idx, val);
        st[p] = max(st[p << 1], st[p << 1 | 1]);
    }

    int query(int p, int l, int r, int L, int R) {
        if (R < l || r < L) return -1;
        if (L <= l && r <= R) return st[p];
        int m = (l + r) >> 1;
        return max(query(p << 1, l, m, L, R),
                   query(p << 1 | 1, m + 1, r, L, R));
    }

    void update(int idx, int val) {
        update(1, 1, n, idx, val);
    }

    int query(int l, int r) {
        return query(1, 1, n, l, r);
    }
};

int n, q;
vector<vector<int>> g;
vector<int> parent_, depth_, heavy, head, pos, sz;
int curPos = 0;

int dfs(int v, int p) {
    parent_[v] = p;
    sz[v] = 1;
    int mx = 0;

    for (int u : g[v]) {
        if (u == p) continue;
        depth_[u] = depth_[v] + 1;
        int s = dfs(u, v);
        sz[v] += s;
        if (s > mx) {
            mx = s;
            heavy[v] = u;
        }
    }
    return sz[v];
}

void decompose(int v, int h) {
    head[v] = h;
    pos[v] = ++curPos;

    if (heavy[v]) decompose(heavy[v], h);

    for (int u : g[v]) {
        if (u == parent_[v] || u == heavy[v]) continue;
        decompose(u, u);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;

    g.assign(n + 1, {});
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    parent_.assign(n + 1, 0);
    depth_.assign(n + 1, 0);
    heavy.assign(n + 1, 0);
    head.assign(n + 1, 0);
    pos.assign(n + 1, 0);
    sz.assign(n + 1, 0);

    dfs(1, 0);
    decompose(1, 1);

    SegTree seg(n);
    vector<int> black(n + 1, 0);

    while (q--) {
        int t, v;
        cin >> t >> v;

        if (t == 0) {
            black[v] ^= 1;
            seg.update(pos[v], black[v] ? depth_[v] + 1 : -1);
        } else {
            vector<pair<int,int>> parts;

            int u = v;
            while (head[u] != head[1]) {
                parts.push_back({pos[head[u]], pos[u]});
                u = parent_[head[u]];
            }
            parts.push_back({pos[1], pos[u]});

            reverse(parts.begin(), parts.end());

            int ans = -1;

            for (auto [l, r] : parts) {
                if (seg.query(l, r) == -1) continue;

                int L = l, R = r, res = r;
                while (L <= R) {
                    int mid = (L + R) >> 1;
                    if (seg.query(l, mid) != -1) {
                        res = mid;
                        R = mid - 1;
                    } else {
                        L = mid + 1;
                    }
                }

                ans = res;
                break;
            }

            if (ans == -1) {
                cout << -1 << '\n';
            } else {
                static vector<int> inv;
                if (inv.empty()) {
                    inv.resize(n + 1);
                    for (int i = 1; i <= n; i++) inv[pos[i]] = i;
                }
                cout << inv[ans] << '\n';
            }
        }
    }

    return 0;
}