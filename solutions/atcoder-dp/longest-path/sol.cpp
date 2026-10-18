// AtCoder Educational DP Contest: G - Longest Path
// longest[v] = most edges on a path ending at v = 1 + max over edges u -> v of longest[u].
// Evaluate in topological order. O(N + M).
#include <bits/stdc++.h>
using namespace std;
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

    vector<int> longest(n + 1, 0);
    for (int u : order)
        for (int v : adj[u]) longest[v] = max(longest[v], longest[u] + 1);
    cout << *max_element(longest.begin(), longest.end()) << "\n";
}
