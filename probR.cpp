#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q;
    if (!(cin >> q)) return 0;

    priority_queue<long long, vector<long long>, greater<long long>> pq;

    while (q--) {
        string cmd;
        cin >> cmd;
        if (cmd == "ADD") {
            long long x;
            cin >> x;
            pq.push(x);
        } else if (cmd == "BUY") {
            if (pq.empty()) {
                cout << -1 << "\n";
            } else {
                cout << pq.top() << "\n";
                pq.pop();
            }
        }
    }

    return 0;
}