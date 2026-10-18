// CSES: Company Queries II
// LCA by binary lifting. Lift the deeper vertex to the other's depth; then lift both by the
// largest jumps that keep them apart. They end just below the LCA. O((n + q) log n).
#include <bits/stdc++.h>
using namespace std;
const int LOG = 18;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<array<int, LOG>> up(n + 1);
    vector<vector<int>> children(n + 1);
    up[1].fill(1);                             // the root is its own ancestor: jumps stop there
    for (int i = 2; i <= n; i++) {
        cin >> up[i][0];
        children[up[i][0]].push_back(i);
    }
    vector<int> depth(n + 1, 0), order = {1};  // BFS order: parents before children
    for (size_t i = 0; i < order.size(); i++)
        for (int c : children[order[i]]) {
            depth[c] = depth[order[i]] + 1;
            order.push_back(c);
        }
    for (int j = 1; j < LOG; j++)
        for (int v : order) up[v][j] = up[up[v][j - 1]][j - 1];
    while (q--) {
        int a, b;
        cin >> a >> b;
        if (depth[a] < depth[b]) swap(a, b);
        for (int j = LOG - 1; j >= 0; j--)
            if (depth[a] - (1 << j) >= depth[b]) a = up[a][j];
        if (a != b) {
            for (int j = LOG - 1; j >= 0; j--)
                if (up[a][j] != up[b][j]) {
                    a = up[a][j];
                    b = up[b][j];
                }
            a = up[a][0];
        }
        cout << a << "\n";
    }
}
