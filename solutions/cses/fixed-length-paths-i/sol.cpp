// CSES: Fixed-Length Paths I
// Centroid decomposition. Every path either passes through the centroid c of the current
// component or lies inside one piece left after deleting c. For c: cnt[d] = number of
// nodes at depth d in the subtrees of c already processed (cnt[0] = 1 for c itself); for
// each new subtree, a node at depth d pairs with cnt[k - d] nodes. Then recurse into the
// pieces, each of size <= half, so every node takes part in O(log n) levels: O(n log n).
// Iterative throughout (recursion over a long path would overflow the stack).
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n, k;
vector<vector<int>> adj;
vector<bool> removed;
vector<int> par, sz, cnt;

int find_centroid(int root) {
    vector<int> order = {root};
    par[root] = 0;
    for (int i = 0; i < (int)order.size(); i++)
        for (int v : adj[order[i]])
            if (!removed[v] && v != par[order[i]]) par[v] = order[i], order.push_back(v);
    int total = order.size();
    for (int i = total - 1; i >= 0; i--) {
        int u = order[i];
        sz[u] = 1;
        for (int v : adj[u])
            if (!removed[v] && v != par[u]) sz[u] += sz[v];
    }
    for (int u : order) {
        int biggest = total - sz[u];        // the part above u
        for (int v : adj[u])
            if (!removed[v] && v != par[u]) biggest = max(biggest, sz[v]);
        if (biggest <= total / 2) return u;
    }
    return root;                            // unreachable: a centroid always exists
}

ll count_through(int c) {
    ll res = 0;
    int maxd = 0;
    cnt[0] = 1;
    for (int s : adj[c]) {
        if (removed[s]) continue;
        vector<pair<int, int>> todo = {{s, 1}};  // (node, depth); BFS within the piece
        par[s] = c;
        for (int i = 0; i < (int)todo.size(); i++) {
            auto [u, d] = todo[i];
            if (d == k) continue;           // deeper nodes cannot be on a k-path through c
            for (int v : adj[u])
                if (!removed[v] && v != par[u]) par[v] = u, todo.push_back({v, d + 1});
        }
        for (auto [u, d] : todo) res += cnt[k - d];
        for (auto [u, d] : todo) cnt[d]++, maxd = max(maxd, d);
    }
    fill(cnt.begin(), cnt.begin() + maxd + 1, 0);
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> k;
    adj.assign(n + 1, {});
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    removed.assign(n + 1, false);
    par.assign(n + 1, 0), sz.assign(n + 1, 0), cnt.assign(n + 1, 0);
    ll ans = 0;
    vector<int> pieces = {1};
    while (!pieces.empty()) {
        int c = find_centroid(pieces.back());
        pieces.pop_back();
        ans += count_through(c);
        removed[c] = true;
        for (int v : adj[c])
            if (!removed[v]) pieces.push_back(v);
    }
    cout << ans << "\n";
}
