#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>

using namespace std;

struct Participant {
    unsigned long long id;
    unsigned long long score;
    bool operator<(const Participant& other) const {
        if (score != other.score) {
            return score > other.score;
        }
        return id < other.id;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q;
    if (!(cin >> q)) return 0;

    map<unsigned long long, unsigned long long> id_to_score;
    set<Participant> leaderboard;
    vector<set<Participant>::iterator> order;

    while (q--) {
        string cmd;
        cin >> cmd;
        if (cmd == "ADD") {
            unsigned long long id, score;
            cin >> id >> score;
            if (id_to_score.count(id)) {
                cout << "FAIL\n";
            } else {
                id_to_score[id] = score;
                leaderboard.insert({id, score});
            }
        } else if (cmd == "UPDATE") {
            unsigned long long id, score;
            cin >> id >> score;
            if (!id_to_score.count(id)) {
                cout << "FAIL\n";
            } else {
                unsigned long long old_score = id_to_score[id];
                leaderboard.erase({id, old_score});
                id_to_score[id] = score;
                leaderboard.insert({id, score});
            }
        } else if (cmd == "REMOVE") {
            unsigned long long id;
            cin >> id;
            if (!id_to_score.count(id)) {
                cout << "FAIL\n";
            } else {
                unsigned long long old_score = id_to_score[id];
                leaderboard.erase({id, old_score});
                id_to_score.erase(id);
            }
        } else if (cmd == "RANK") {
            unsigned long long id;
            cin >> id;
            if (!id_to_score.count(id)) {
                cout << "FAIL\n";
            } else {
                unsigned long long score = id_to_score[id];
                Participant p = {id, score};
                int r = 1;
                for (auto it = leaderboard.begin(); it != leaderboard.end(); ++it) {
                    if (it->id == p.id) break;
                    r++;
                }
                cout << r << "\n";
            }
        } else if (cmd == "KTH") {
            int k;
            cin >> k;
            if (k < 1 || k > (int)leaderboard.size()) {
                cout << "INVALID\n";
            } else {
                auto it = leaderboard.begin();
                advance(it, k - 1);
                cout << it->id << " " << it->score << "\n";
            }
        } else if (cmd == "MEDIAN") {
            if (leaderboard.empty()) {
                cout << "EMPTY\n";
            } else {
                int n = leaderboard.size();
                int mid = (n + 1) / 2;
                auto it = leaderboard.begin();
                advance(it, mid - 1);
                cout << it->id << " " << it->score << "\n";
            }
        }
    }
    return 0;
}