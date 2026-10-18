// CSES: Counting Rooms
// Count connected components of floor cells: start a flood fill (BFS) from every
// unvisited floor cell. Each cell is visited once: O(nm).
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<string> g(n);
    for (auto& row : g) cin >> row;
    const int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};

    int rooms = 0;
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            if (g[r][c] != '.') continue;
            rooms++;
            queue<pair<int, int>> q;
            q.push({r, c});
            g[r][c] = '#';                       // mark visited by turning it into wall
            while (!q.empty()) {
                auto [y, x] = q.front();
                q.pop();
                for (int d = 0; d < 4; d++) {
                    int ny = y + dr[d], nx = x + dc[d];
                    if (ny < 0 || ny >= n || nx < 0 || nx >= m || g[ny][nx] != '.') continue;
                    g[ny][nx] = '#';
                    q.push({ny, nx});
                }
            }
        }
    }
    cout << rooms << "\n";
}
