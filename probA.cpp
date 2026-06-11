#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int children[128]; 
    int count; 
    TreeNode() : count(0) { fill(children, children+128, -1); }
};

vector<TreeNode> trie;

void insert(const string& w) {
    int cur = 0;
    for (char c : w) {
        int idx = (unsigned char)c;
        if (trie[cur].children[idx] == -1) {
            trie[cur].children[idx] = trie.size();
            trie.push_back(TreeNode());
        }
        cur = trie[cur].children[idx];
        trie[cur].count++;
    }
}

int query(const string& s) {
    int cur = 0;
    for (char c : s) {
        int idx = (unsigned char)c;
        if (trie[cur].children[idx] == -1) return 0;
        cur = trie[cur].children[idx];
    }
    return trie[cur].count;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    trie.push_back(TreeNode()); // root
    
    int n; cin >> n;
    while (n--) {
        string w; cin >> w;
        insert(w);
    }
    
    int q; cin >> q;
    while (q--) {
        string s; cin >> s;
        cout << query(s) << "\n";
    }
    return 0;
}