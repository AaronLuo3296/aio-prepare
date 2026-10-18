// CSES: Message Route
// BFS from computer 1 gives shortest distances in an unweighted graph; remembering each
// vertex's BFS parent lets us walk the route back from n. O(n + m).
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> parent(n + 1, -1);
    queue<int> q;
    q.push(1);
    parent[1] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u])
            if (parent[v] == -1) {
                parent[v] = u;
                q.push(v);
            }
    }
    if (parent[n] == -1) {
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
