// CSES: Tree Diameter
// BFS from any vertex; the farthest vertex a is an end of some diameter. BFS again from a:
// the largest distance is the diameter. O(n).
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
    vector<int> d2 = bfs(adj, a);
    cout << *max_element(d2.begin(), d2.end()) << "\n";
}
