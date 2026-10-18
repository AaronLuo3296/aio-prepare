// CSES: Monsters
// 1. Multi-source BFS from all monsters at once: mon[c] = earliest time a monster can be on c.
// 2. BFS from A, entering a cell only if we arrive strictly before every monster.
// Reaching any border cell means escape; rebuild the path as in Labyrinth. O(nm).
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
    const int INF = INT_MAX;

    vector<vector<int>> mon(n, vector<int>(m, INF)), me(n, vector<int>(m, INF));
    vector<vector<int>> how(n, vector<int>(m, -1));
    queue<pair<int, int>> q;
    int sr = 0, sc = 0;
    for (int r = 0; r < n; r++)
        for (int c = 0; c < m; c++) {
            if (g[r][c] == 'M') mon[r][c] = 0, q.push({r, c});
            if (g[r][c] == 'A') sr = r, sc = c;
        }

    auto bfs = [&](vector<vector<int>>& dist, bool isMe) {
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();
            if (isMe && (r == 0 || r == n - 1 || c == 0 || c == m - 1)) return make_pair(r, c);
            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d], nc = c + dc[d];
                if (nr < 0 || nr >= n || nc < 0 || nc >= m || g[nr][nc] == '#') continue;
                if (dist[nr][nc] != INF) continue;
                if (isMe && dist[r][c] + 1 >= mon[nr][nc]) continue;   // a monster gets there first
                dist[nr][nc] = dist[r][c] + 1;
                if (isMe) how[nr][nc] = d;
                q.push({nr, nc});
            }
        }
        return make_pair(-1, -1);
    };

    bfs(mon, false);
    me[sr][sc] = 0;
    q.push({sr, sc});
    auto [er, ec] = bfs(me, true);
    if (er == -1) {
        cout << "NO\n";
        return 0;
    }
    string path;
    for (int r = er, c = ec; r != sr || c != sc;) {
        int d = how[r][c];
        path += name[d];
        r -= dr[d], c -= dc[d];
    }
    reverse(path.begin(), path.end());
    cout << "YES\n" << path.size() << "\n" << path << "\n";
}
