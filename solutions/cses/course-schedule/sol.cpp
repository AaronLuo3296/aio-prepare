// CSES: Course Schedule
// Topological sort (Kahn). If some vertex never reaches in-degree 0, it lies on or after
// a directed cycle, so no order exists. O(n + m).
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
    if ((int)order.size() < n) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    for (int v : order) cout << v << " ";
    cout << "\n";
}
