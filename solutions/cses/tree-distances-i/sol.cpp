// CSES: Tree Distances I
// The farthest vertex from any v is one of the two ends a, b of a diameter, so the answer
// for v is max(dist(a, v), dist(b, v)). Three BFS runs: O(n).
#include <bits/stdc++.h>
using namespace std;
vector<int> bfs(const vector<vector<int>>& adj, int src) {
    vector<int> dist(adj.size(), -1);
    queue<int> q;
    q.push(src);
    dist[src] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u])
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
    }
    return dist;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<int> d1 = bfs(adj, 1);
    int a = max_element(d1.begin(), d1.end()) - d1.begin();
    vector<int> da = bfs(adj, a);
    int b = max_element(da.begin(), da.end()) - da.begin();
    vector<int> db = bfs(adj, b);
    for (int v = 1; v <= n; v++) cout << max(da[v], db[v]) << " ";
    cout << "\n";
}
