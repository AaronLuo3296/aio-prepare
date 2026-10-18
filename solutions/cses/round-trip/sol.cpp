// CSES: Round Trip
// DFS that remembers which vertices are on the current path. In an undirected graph a
// neighbour that is on the path and is not our parent closes a cycle of length >= 3.
// Iterative DFS (explicit stack + next-edge index) avoids deep recursion. O(n + m).
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

    vector<int> parent(n + 1, 0), state(n + 1, 0), nextEdge(n + 1, 0);  // state: 0 new, 1 on path, 2 done
    for (int s = 1; s <= n; s++) {
        if (state[s]) continue;
        vector<int> path = {s};
        state[s] = 1;
        while (!path.empty()) {
            int u = path.back();
            if (nextEdge[u] == (int)adj[u].size()) {
                state[u] = 2;
                path.pop_back();
                continue;
            }
            int v = adj[u][nextEdge[u]++];
            if (v == parent[u]) continue;
            if (state[v] == 1) {                 // cycle v -> ... -> u -> v
                vector<int> cycle = {v};
                for (int x = u; x != v; x = parent[x]) cycle.push_back(x);
                cycle.push_back(v);
                cout << cycle.size() << "\n";
                for (int x : cycle) cout << x << " ";
                cout << "\n";
                return 0;
            }
            if (state[v] == 0) {
                state[v] = 1;
                parent[v] = u;
                path.push_back(v);
            }
        }
    }
    cout << "IMPOSSIBLE\n";
}
