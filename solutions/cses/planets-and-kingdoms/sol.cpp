// CSES: Planets and Kingdoms
// Kosaraju: (1) DFS on the graph, recording nodes in order of finishing time; (2) take
// nodes in reverse finishing order and flood-fill the REVERSED graph; each flood is one
// strongly connected component. The first DFS is iterative (a 10^5-node path would
// overflow the call stack). O(n + m).
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n + 1), rg(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        rg[b].push_back(a);
    }
    vector<int> order, it(n + 1, 0);
    vector<bool> seen(n + 1, false);
    for (int s = 1; s <= n; s++) {
        if (seen[s]) continue;
        vector<int> st = {s};
        seen[s] = true;
        while (!st.empty()) {
            int u = st.back();
            if (it[u] < (int)g[u].size()) {
                int v = g[u][it[u]++];
                if (!seen[v]) seen[v] = true, st.push_back(v);
            } else {
                order.push_back(u);         // u finished
                st.pop_back();
            }
        }
    }
    vector<int> comp(n + 1, 0);
    int k = 0;
    for (int i = n - 1; i >= 0; i--) {
        int s = order[i];
        if (comp[s]) continue;
        comp[s] = ++k;
        vector<int> st = {s};
        while (!st.empty()) {
            int u = st.back();
            st.pop_back();
            for (int v : rg[u])
                if (!comp[v]) comp[v] = k, st.push_back(v);
        }
    }
    cout << k << "\n";
    for (int v = 1; v <= n; v++) cout << comp[v] << " \n"[v == n];
}
