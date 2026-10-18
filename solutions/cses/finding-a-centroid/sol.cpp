// CSES: Finding a Centroid
// Root at 1 and compute subtree sizes. Start at the root and step into the child whose
// subtree has more than n/2 nodes while one exists. The part "above" the current node only
// shrinks below n/2 as we descend, so the walk stops at a centroid. O(n), iterative.
#include <bits/stdc++.h>
using namespace std;
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
    vector<int> order = {1}, par(n + 1, 0), sz(n + 1, 1);
    for (int i = 0; i < (int)order.size(); i++)
        for (int v : adj[order[i]])
            if (v != par[order[i]]) par[v] = order[i], order.push_back(v);
    for (int i = n - 1; i > 0; i--) sz[par[order[i]]] += sz[order[i]];
    int c = 1;
    for (bool moved = true; moved;) {
        moved = false;
        for (int v : adj[c])
            if (v != par[c] && sz[v] > n / 2) {
                c = v, moved = true;
                break;
            }
    }
    cout << c << "\n";
}
