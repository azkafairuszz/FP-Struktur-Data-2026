#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;

// Use an order-statistics structure: policy-based or manual
// We need: add, remove, update, rank(id), kth(k), median
// Key: (-score, id) for ordering (rank 1 = highest score, ties broken by smaller id)
// Use a sorted multiset/set

map<ll,ll> score_of; // id -> score
set<pll> board; // (-score, id) sorted

int sz() { return board.size(); }

// Fenwick for order statistics is complex with large IDs; use set + order
// For rank: count elements < (-score, id) in board, that's rank-1 before it
// Actually set is sorted, can use distance but O(n)
// Since Q<=3e5 and operations, use ordered set (GNU policy)
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<pll,null_type,less<pll>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;

ordered_set os;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int q; cin >> q;
    while (q--) {
        string op; cin >> op;
        if (op == "ADD") {
            ll id, sc; cin >> id >> sc;
            if (score_of.count(id)) { cout << "FAIL\n"; }
            else {
                score_of[id] = sc;
                os.insert({-sc, id});
            }
        } else if (op == "UPDATE") {
            ll id, sc; cin >> id >> sc;
            if (!score_of.count(id)) { cout << "FAIL\n"; }
            else {
                ll old = score_of[id];
                os.erase({-old, id});
                score_of[id] = sc;
                os.insert({-sc, id});
            }
        } else if (op == "REMOVE") {
            ll id; cin >> id;
            if (!score_of.count(id)) { cout << "FAIL\n"; }
            else {
                ll old = score_of[id];
                os.erase({-old, id});
                score_of.erase(id);
            }
        } else if (op == "RANK") {
            ll id; cin >> id;
            if (!score_of.count(id)) { cout << "FAIL\n"; }
            else {
                ll sc = score_of[id];
                int r = os.order_of_key({-sc, id}) + 1;
                cout << r << "\n";
            }
        } else if (op == "KTH") {
            int k; cin >> k;
            if (k > (int)os.size()) { cout << "INVALID\n"; }
            else {
                auto it = os.find_by_order(k-1);
                cout << it->second << " " << -(it->first) << "\n";
            }
        } else { // MEDIAN
            if (os.empty()) { cout << "EMPTY\n"; }
            else {
                int n = os.size();
                int med = (n+1+1)/2; // ceil((n+1)/2)
                // median pos = floor((n+1)/2) ... wait: ceil((n+1)/2)
                // if n=1: pos=1, n=2: pos=1 (floor(3/2)=1), n=3: pos=2
                // floor((n+1)/2)
                int pos = (n+1)/2;
                auto it = os.find_by_order(pos-1);
                cout << it->second << " " << -(it->first) << "\n";
            }
        }
    }
}