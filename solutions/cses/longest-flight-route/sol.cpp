// CSES: Longest Flight Route
// DP over a topological order: best[v] = most cities on a route 1 -> v
// (0 = unreachable). Process u before its successors, so best[u] is final when used. O(n + m).
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

    vector<int> best(n + 1, 0), parent(n + 1, 0);
    best[1] = 1;
    for (int u : order) {
        if (best[u] == 0) continue;
        for (int v : adj[u])
            if (best[u] + 1 > best[v]) {
                best[v] = best[u] + 1;
                parent[v] = u;
            }
    }
    if (best[n] == 0) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    vector<int> route;
    for (int v = n; v != 0; v = parent[v]) route.push_back(v);
    reverse(route.begin(), route.end());
    cout << route.size() << "\n";
    for (int v : route) cout << v << " ";
    cout << "\n";
}
