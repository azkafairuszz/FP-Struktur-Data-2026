#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> par, rnk;
    int comp;
    DSU(int n) : par(n), rnk(n,0), comp(n) {
        iota(par.begin(), par.end(), 0);
    }
    int find(int x) {
        if (par[x]!=x) par[x]=find(par[x]);
        return par[x];
    }
    void unite(int a, int b) {
        a=find(a); b=find(b);
        if (a==b) return;
        comp--;
        if (rnk[a]<rnk[b]) swap(a,b);
        par[b]=a;
        if (rnk[a]==rnk[b]) rnk[a]++;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M; cin >> N >> M;
    vector<pair<int,int>> bridges(M+1);
    for (int i=1;i<=M;i++) cin >> bridges[i].first >> bridges[i].second;
    
    int Q; cin >> Q;
    vector<int> collapse(Q);
    for (int i=0;i<Q;i++) cin >> collapse[i];

    set<int> collapsed(collapse.begin(), collapse.end());
    
    DSU dsu(N+1);
    for (int i=1;i<=M;i++) {
        if (!collapsed.count(i)) {
            dsu.unite(bridges[i].first, bridges[i].second);
        }
    }
    
    vector<int> rev_ans(Q);
    for (int i=Q-1;i>=0;i--) {
        rev_ans[i] = dsu.comp - 1; 
        dsu.unite(bridges[collapse[i]].first, bridges[collapse[i]].second);
    }
    
    for (int i=0;i<Q;i++) cout << rev_ans[i] << "\n";
    return 0;
}