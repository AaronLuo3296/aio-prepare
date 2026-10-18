// CSES: Game Routes
// Counting DP over a topological order: ways[v] = sum of ways[u] over edges u -> v,
// ways[1] = 1. O(n + m).
#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    vector<int> indeg(n + 1, 0);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        indeg[b]++;
    }
    // Kahn's algorithm: repeatedly remove a vertex with no remaining incoming edges.
    vector<int> order;
    queue<int> q;
    for (int v = 1; v <= n; v++)
        if (indeg[v] == 0) q.push(v);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        order.push_back(u);
        for (int v : adj[u])
            if (--indeg[v] == 0) q.push(v);
    }

    vector<int> ways(n + 1, 0);
    ways[1] = 1;
    for (int u : order)
        for (int v : adj[u]) ways[v] = (ways[v] + ways[u]) % MOD;
    cout << ways[n] << "\n";
}
