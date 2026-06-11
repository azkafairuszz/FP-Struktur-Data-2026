#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> par, rnk;
    int components;
    DSU(int n) : par(n), rnk(n,0), components(n) {
        iota(par.begin(), par.end(), 0);
    }
    int find(int x) {
        if (par[x]!=x) par[x]=find(par[x]);
        return par[x];
    }
    void unite(int a, int b) {
        a=find(a); b=find(b);
        if (a==b) return;
        components--;
        if (rnk[a]<rnk[b]) swap(a,b);
        par[b]=a;
        if (rnk[a]==rnk[b]) rnk[a]++;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, Q; cin >> N >> Q;
    vector<long long> X(N), Y(N);
    for (int i=0;i<N;i++) cin >> X[i] >> Y[i];
    
    // Build edges
    vector<pair<long long,pair<int,int>>> edges;
    for (int i=0;i<N;i++)
        for (int j=i+1;j<N;j++) {
            long long dx=X[i]-X[j], dy=Y[i]-Y[j];
            edges.push_back({dx*dx+dy*dy, {i,j}});
        }
    sort(edges.begin(), edges.end());
    
    // Read queries
    vector<pair<long long,int>> queries(Q);
    for (int i=0;i<Q;i++) {
        cin >> queries[i].first;
        queries[i].second = i;
    }
   
    vector<pair<long long,int>> sorted_q = queries;
    sort(sorted_q.begin(), sorted_q.end());
    
    vector<int> ans(Q);
    DSU dsu(N);
    int ei = 0;
    
    for (auto& [p, qi] : sorted_q) {
        if (p == 0) {
        }
        while (ei < (int)edges.size() && edges[ei].first <= p) {
            dsu.unite(edges[ei].second.first, edges[ei].second.second);
            ei++;
        }
        ans[qi] = dsu.components;
    }
    
    for (int i=0;i<Q;i++) cout << ans[i] << "\n";
    return 0;
}