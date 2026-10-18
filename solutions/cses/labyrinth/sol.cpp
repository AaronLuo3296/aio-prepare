// CSES: Labyrinth
// BFS on the grid from A. Store the move used to enter each cell, then walk back from B
// to rebuild the path. O(nm).
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<string> g(n);
    for (auto& row : g) cin >> row;
    const int dr[] = {-1, 1, 0, 0}, dc[] = {0, 0, -1, 1};
    const string name = "UDLR";

    int sr = 0, sc = 0, er = 0, ec = 0;
    for (int r = 0; r < n; r++)
        for (int c = 0; c < m; c++) {
            if (g[r][c] == 'A') sr = r, sc = c;
            if (g[r][c] == 'B') er = r, ec = c;
        }

    vector<vector<int>> how(n, vector<int>(m, -1));   // move index used to arrive, -1 = unseen
    queue<pair<int, int>> q;
    q.push({sr, sc});
    how[sr][sc] = 4;                                   // 4 marks the start
    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
            if (g[nr][nc] == '#' || how[nr][nc] != -1) continue;
            how[nr][nc] = d;
            q.push({nr, nc});
        }
    }
    if (how[er][ec] == -1) {
        cout << "NO\n";
        return 0;
    }
    string path;
    for (int r = er, c = ec; how[r][c] != 4;) {
        int d = how[r][c];
        path += name[d];
        r -= dr[d], c -= dc[d];
    }
    reverse(path.begin(), path.end());
    cout << "YES\n" << path.size() << "\n" << path << "\n";
}
