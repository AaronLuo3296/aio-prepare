// CSES: Flight Routes Check
// The graph is strongly connected iff every city is reachable from city 1 in the graph AND
// in the reversed graph. If v is unreachable from 1, answer "1 v"; if 1 is unreachable
// from v (v unseen in the reversed search), answer "v 1". Two DFS: O(n + m).
#include <bits/stdc++.h>
using namespace std;

vector<bool> reach(const vector<vector<int>> &g, int s) {
    vector<bool> seen(g.size(), false);
    vector<int> st = {s};
    seen[s] = true;
    while (!st.empty()) {
        int u = st.back();
        st.pop_back();
        for (int v : g[u])
            if (!seen[v]) seen[v] = true, st.push_back(v);
    }
    return seen;
}

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
    vector<bool> fw = reach(g, 1), bw = reach(rg, 1);
    for (int v = 1; v <= n; v++) {
        if (!fw[v]) return cout << "NO\n1 " << v << "\n", 0;
        if (!bw[v]) return cout << "NO\n" << v << " 1\n", 0;
    }
    cout << "YES\n";
}
