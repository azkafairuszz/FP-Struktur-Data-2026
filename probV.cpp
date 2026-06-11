#include <bits/stdc++.h>
using namespace std;

struct TwoSAT {
    int n;
    vector<vector<int>> g, rg;
    vector<int> comp, vis, order;

    TwoSAT(int n) : n(n) {
        g.assign(2 * n, {});
        rg.assign(2 * n, {});
    }

    int id(int x, bool val) {
        return 2 * x + (val ? 1 : 0);
    }

    void addImp(int a, int b) {
        g[a].push_back(b);
        rg[b].push_back(a);
    }

    void addOr(int a, int b) {
        addImp(a ^ 1, b);
        addImp(b ^ 1, a);
    }

    void dfs1(int v) {
        vis[v] = 1;
        for (int u : g[v])
            if (!vis[u]) dfs1(u);
        order.push_back(v);
    }

    void dfs2(int v, int c) {
        comp[v] = c;
        for (int u : rg[v])
            if (comp[u] == -1) dfs2(u, c);
    }

    bool satisfiable() {
        vis.assign(2 * n, 0);
        for (int i = 0; i < 2 * n; i++)
            if (!vis[i]) dfs1(i);

        comp.assign(2 * n, -1);

        int j = 0;
        for (int i = (int)order.size() - 1; i >= 0; i--) {
            int v = order[i];
            if (comp[v] == -1) dfs2(v, j++);
        }

        for (int i = 0; i < n; i++)
            if (comp[2 * i] == comp[2 * i + 1])
                return false;

        return true;
    }
};

struct Schedule {
    long long t, l, r;
};

bool collide(const Schedule& a, const Schedule& b) {
    if (a.t != b.t) return false;
    return max(a.l, b.l) < min(a.r, b.r);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<Schedule> A(N), B(N);

    for (int i = 0; i < N; i++) {
        cin >> A[i].t >> A[i].l >> A[i].r
            >> B[i].t >> B[i].l >> B[i].r;
    }

    TwoSAT sat(N);

    for (int i = 0; i < N; i++) {
        int x = 2 * i + 1;
        int nx = 2 * i;

        sat.addOr(x, nx);
        sat.addOr(x ^ 1, nx ^ 1);
    }

    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            bool cAA = collide(A[i], A[j]);
            bool cAB = collide(A[i], B[j]);
            bool cBA = collide(B[i], A[j]);
            bool cBB = collide(B[i], B[j]);

            int Ai = 2 * i + 1;
            int Bi = 2 * i;
            int Aj = 2 * j + 1;
            int Bj = 2 * j;

            if (cAA) sat.addOr(Ai ^ 1, Aj ^ 1);
            if (cAB) sat.addOr(Ai ^ 1, Bj ^ 1);
            if (cBA) sat.addOr(Bi ^ 1, Aj ^ 1);
            if (cBB) sat.addOr(Bi ^ 1, Bj ^ 1);
        }
    }

    cout << (sat.satisfiable() ? "RIFT SEALED" : "RIFT COLLAPSED") << '\n';
    return 0;
}