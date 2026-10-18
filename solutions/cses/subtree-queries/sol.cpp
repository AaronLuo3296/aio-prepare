// CSES: Subtree Queries
// Euler tour: number vertices in DFS order (tin). A subtree is then the contiguous block
// [tin[s], tin[s] + size[s]), so subtree sum = range sum on a Fenwick tree. O((n + q) log n).
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int n;
vector<ll> bit;
void add(int i, ll d) {
    for (; i <= n; i += i & -i) bit[i] += d;
}
ll prefix(int i) {
    ll s = 0;
    for (; i > 0; i -= i & -i) s += bit[i];
    return s;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int q;
    cin >> n >> q;
    vector<ll> val(n + 1);
    for (int i = 1; i <= n; i++) cin >> val[i];
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    // Iterative DFS (a path of 2e5 vertices would overflow a recursive one).
    vector<int> tin(n + 1, 0), sz(n + 1, 1), parent(n + 1, 0), order;
    vector<int> st = {1};
    while (!st.empty()) {
        int u = st.back();
        st.pop_back();
        tin[u] = order.size() + 1;
        order.push_back(u);
        for (int v : adj[u])
            if (v != parent[u]) {
                parent[v] = u;
                st.push_back(v);
            }
    }
    for (int i = n - 1; i > 0; i--) sz[parent[order[i]]] += sz[order[i]];
    bit.assign(n + 1, 0);
    for (int v = 1; v <= n; v++) add(tin[v], val[v]);
    while (q--) {
        int type, s;
        cin >> type >> s;
        if (type == 1) {
            ll x;
            cin >> x;
            add(tin[s], x - val[s]);
            val[s] = x;
        } else {
            cout << prefix(tin[s] + sz[s] - 1) - prefix(tin[s] - 1) << "\n";
        }
    }
}
