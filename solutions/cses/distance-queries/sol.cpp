// CSES: Distance Queries
// Root at 1. The path a-b goes up to lca(a, b) and down again, so
// dist(a, b) = depth[a] + depth[b] - 2 * depth[lca]. LCA by binary lifting. O((n + q) log n).
#include <bits/stdc++.h>
using namespace std;
const int LOG = 18;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<array<int, LOG>> up(n + 1);
    vector<int> parent(n + 1, 0), depth(n + 1, 0), order = {1};
    for (size_t i = 0; i < order.size(); i++) {  // BFS order: parents before children
        int u = order[i];
        for (int v : adj[u])
            if (v != parent[u]) {
                parent[v] = u;
                depth[v] = depth[u] + 1;
                order.push_back(v);
            }
    }
    up[1].fill(1);                             // the root is its own ancestor
    for (int v = 2; v <= n; v++) up[v][0] = parent[v];
    for (int j = 1; j < LOG; j++)
        for (int v : order) up[v][j] = up[up[v][j - 1]][j - 1];
    auto lca = [&](int a, int b) {
        if (depth[a] < depth[b]) swap(a, b);
        for (int j = LOG - 1; j >= 0; j--)
            if (depth[a] - (1 << j) >= depth[b]) a = up[a][j];
        if (a == b) return a;
        for (int j = LOG - 1; j >= 0; j--)
            if (up[a][j] != up[b][j]) {
                a = up[a][j];
                b = up[b][j];
            }
        return up[a][0];
    };
    while (q--) {
        int a, b;
        cin >> a >> b;
        cout << depth[a] + depth[b] - 2 * depth[lca(a, b)] << "\n";
    }
}
