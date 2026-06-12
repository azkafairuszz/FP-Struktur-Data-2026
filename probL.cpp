#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    unordered_map<string, array<int,3>> info; // name -> {region_idx, pos, ring_size}
    vector<int> ringSize(n);
    for (int i = 0; i < n; i++) {
        string region; cin >> region;
        vector<string> names;
        string tok;
        while (cin >> tok && tok != "end") {
            names.push_back(tok);
        }
        int sz = names.size();
        ringSize[i] = sz;
        for (int p = 0; p < sz; p++) {
            info[names[p]] = {i, p, sz};
        }
    }
    int t; cin >> t;
    while (t--) {
        string a, b; int k;
        cin >> a >> b >> k;
        auto ia = info.find(a);
        auto ib = info.find(b);
        if (ia == info.end() || ib == info.end()) {
            cout << "Signal lost\n";
            continue;
        }
        auto [rA, pA, sA] = ia->second;
        auto [rB, pB, sB] = ib->second;
        int dist;
        if (rA == rB) {
            int d = abs(pA - pB);
            dist = min(d, sA - d);
        } else {
            int dA = abs(pA - 0);
            int ringA = min(dA, sA - dA);
            int dB = abs(0 - pB);
            int ringB = min(dB, sB - dB);
            int dR = abs(rA - rB);
            int ringR = min(dR, n - dR);
            dist = (ringA + 1) + ringR + (1 + ringB);
        }
        if (dist <= k) {
            cout << "Connected on " << dist << " second\n";
        } else {
            cout << "Signal lost\n";
        }
    }
}