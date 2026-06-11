#include <bits/stdc++.h>
using namespace std;

unordered_map<int,int> dept;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t; cin >> t;
    for (int d = 0; d < t; d++) {
        int n; cin >> n;
        while (n--) {
            int id; cin >> id;
            dept[id] = d;
        }
    }
    
    list<int> q;
    unordered_map<int, list<int>::iterator> tail;
    unordered_map<int, int> dept_count;
    
    string cmd;
    while (cin >> cmd) {
        if (cmd == "ENQUEUE") {
            int x; cin >> x;
            int d = dept[x];
            if (dept_count[d] > 0) {
                auto it = tail[d];
                ++it;
                tail[d] = q.insert(it, x);
            } else {
                q.push_back(x);
                tail[d] = prev(q.end());
            }
            dept_count[d]++;
        } else { // DEQUEUE
            if (q.empty()) continue;
            int front = q.front();
            int d = dept[front];
            q.pop_front();
            cout << front << "\n";
            dept_count[d]--;
        }
    }
    return 0;
}