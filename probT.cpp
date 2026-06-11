#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    int qx, qy;
    cin >> qx >> qy;

    int kx, ky;
    cin >> kx >> ky;

    int tx, ty;
    cin >> tx >> ty;

    vector<vector<bool>> blocked(n + 1, vector<bool>(n + 1, false));
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        blocked[x][y] = true;
    }

    vector<vector<bool>> danger(n + 1, vector<bool>(n + 1, false));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == qx || j == qy || abs(i - qx) == abs(j - qy)) {
                danger[i][j] = true;
            }
        }
    }

    if (danger[kx][ky] || danger[tx][ty] || blocked[kx][ky] || blocked[tx][ty]) {
        cout << "Nay\n";
        return 0;
    }

    queue<pair<int, int>> q;
    vector<vector<bool>> visited(n + 1, vector<bool>(n + 1, false));

    q.push({kx, ky});
    visited[kx][ky] = true;

    bool reached = false;

    while (!q.empty()) {
        auto [cx, cy] = q.front();
        q.pop();

        if (cx == tx && cy == ty) {
            reached = true;
            break;
        }

        for (int i = 0; i < 8; i++) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];

            if (nx >= 1 && nx <= n && ny >= 1 && ny <= n) {
                if (!visited[nx][ny] && !blocked[nx][ny] && !danger[nx][ny]) {
                    visited[nx][ny] = true;
                    q.push({nx, ny});
                }
            }
        }
    }

    if (reached) {
        cout << "Yay\n";
    } else {
        cout << "Nay\n";
    }

    return 0;
}