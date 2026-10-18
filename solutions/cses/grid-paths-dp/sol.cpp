// CSES: Grid Paths (Dynamic Programming section)
// Lattice-path recurrence: paths[r][c] = paths[r-1][c] + paths[r][c-1], 0 on traps. O(n^2).
#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<string> g(n);
    for (auto& row : g) cin >> row;
    vector<vector<int>> paths(n, vector<int>(n, 0));
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (g[r][c] == '*') continue;
            if (r == 0 && c == 0) paths[r][c] = 1;
            if (r > 0) paths[r][c] = (paths[r][c] + paths[r - 1][c]) % MOD;
            if (c > 0) paths[r][c] = (paths[r][c] + paths[r][c - 1]) % MOD;
        }
    }
    cout << paths[n - 1][n - 1] << "\n";
}
