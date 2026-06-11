#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int q; cin >> q;
    deque<string> dq;
    
    while (q--) {
        string cmd; cin >> cmd;
        if (cmd == "PUSH_FRONT") {
            string x; cin >> x;
            dq.push_front(x);
        } else if (cmd == "PUSH_BACK") {
            string x; cin >> x;
            dq.push_back(x);
        } else if (cmd == "POP_FRONT") {
            if (!dq.empty()) dq.pop_front();
        } else { // POP_BACK
            if (!dq.empty()) dq.pop_back();
        }
    }
    
    if (dq.empty()) {
        cout << "KOSONG\n";
    } else {
        for (int i = 0; i < (int)dq.size(); i++) {
            if (i) cout << " ";
            cout << dq[i];
        }
        cout << "\n";
    }
    return 0;
}