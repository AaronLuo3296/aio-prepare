// CSES: Tree Distances II
// Rerooting. Root at 1: sz[v] = subtree size, ans[1] = sum of depths. Moving the root from
// parent p to child v brings sz[v] nodes one step closer and n - sz[v] one step further:
// ans[v] = ans[p] + n - 2*sz[v]. Iterative DFS order (a path of 2*10^5 nodes would
// overflow the recursion stack). O(n).
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
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
    vector<int> order, par(n + 1, 0), dep(n + 1, 0);
    vector<ll> sz(n + 1, 1), ans(n + 1, 0);
    order.reserve(n);
    vector<int> st = {1};
    par[1] = -1;
    while (!st.empty()) {                   // preorder: parents before children
        int u = st.back();
        st.pop_back();
        order.push_back(u);
        for (int v : adj[u])
            if (v != par[u]) par[v] = u, dep[v] = dep[u] + 1, st.push_back(v);
    }
    for (int i = n - 1; i > 0; i--) sz[par[order[i]]] += sz[order[i]];
    for (int v = 1; v <= n; v++) ans[1] += dep[v];
    for (int i = 1; i < n; i++) {
        int v = order[i];
        ans[v] = ans[par[v]] + n - 2 * sz[v];
    }
    for (int v = 1; v <= n; v++) cout << ans[v] << " \n"[v == n];
}
