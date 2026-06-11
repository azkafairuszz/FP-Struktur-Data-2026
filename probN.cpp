#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    stack<string> carrier;

    while (n--) {
        string cmd;
        cin >> cmd;
        if (cmd == "PUSH") {
            string x;
            cin >> x;
            carrier.push(x);
        } else if (cmd == "POP") {
            if (!carrier.empty()) {
                carrier.pop();
            }
        } else if (cmd == "TOP") {
            if (carrier.empty()) {
                cout << "KOSONG\n";
            } else {
                cout << carrier.top() << "\n";
            }
        }
    }

    return 0;
}