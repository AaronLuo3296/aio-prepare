// CSES: Path Queries II
// Heavy-light decomposition. The heavy child of v is its child with the largest subtree.
// Heavy edges form chains; laying each chain out contiguously puts every chain on one
// interval of a segment tree. Any root-to-node path crosses O(log n) light edges (each one
// at least halves the subtree size), so a path query is O(log n) chain pieces, each an
// O(log n) segment tree query: O(log^2 n) per query. Everything is iterative because a
// path-shaped tree of 2*10^5 nodes would overflow the recursion stack.
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<int> val(n + 1);
    for (int i = 1; i <= n; i++) cin >> val[i];
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<int> order = {1}, par(n + 1, 0), dep(n + 1, 0), sz(n + 1, 1), heavy(n + 1, 0);
    for (int i = 0; i < (int)order.size(); i++) {      // BFS: parents before children
        int u = order[i];
        for (int v : adj[u])
            if (v != par[u]) par[v] = u, dep[v] = dep[u] + 1, order.push_back(v);
    }
    for (int i = n - 1; i > 0; i--) {
        int v = order[i], p = par[v];
        sz[p] += sz[v];
        if (!heavy[p] || sz[v] > sz[heavy[p]]) heavy[p] = v;
    }
    vector<int> head(n + 1), pos(n + 1);
    int cur = 0;
    for (int v : order)                     // v starts a chain unless it is a heavy child
        if (v == 1 || heavy[par[v]] != v)
            for (int u = v; u; u = heavy[u]) head[u] = v, pos[u] = cur++;
    vector<int> t(2 * n);                   // bottom-up max segment tree over positions
    for (int v = 1; v <= n; v++) t[n + pos[v]] = val[v];
    for (int i = n - 1; i > 0; i--) t[i] = max(t[2 * i], t[2 * i + 1]);
    auto query = [&](int l, int r) {        // max over positions [l, r]
        int res = 0;
        for (l += n, r += n + 1; l < r; l /= 2, r /= 2) {
            if (l & 1) res = max(res, t[l++]);
            if (r & 1) res = max(res, t[--r]);
        }
        return res;
    };
    while (q--) {
        int type, a, b;
        cin >> type >> a >> b;
        if (type == 1) {
            int i = n + pos[a];
            for (t[i] = b; i > 1; i /= 2) t[i / 2] = max(t[i], t[i ^ 1]);
            continue;
        }
        int res = 0;
        while (head[a] != head[b]) {        // lift the endpoint whose chain head is deeper
            if (dep[head[a]] < dep[head[b]]) swap(a, b);
            res = max(res, query(pos[head[a]], pos[a]));
            a = par[head[a]];
        }
        if (dep[a] > dep[b]) swap(a, b);
        res = max(res, query(pos[a], pos[b]));
        cout << res << " ";
    }
    cout << "\n";
}
