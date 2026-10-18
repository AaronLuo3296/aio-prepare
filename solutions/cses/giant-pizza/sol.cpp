// CSES: Giant Pizza
// 2-SAT. Literal "topping x included" is node 2x, "not included" is 2x+1 (so ^1 negates).
// Wish (a or b) gives implications not a -> b and not b -> a. Unsatisfiable iff some x and
// not x share a strongly connected component. Otherwise set x true iff comp[x] comes later
// in Kosaraju's discovery order than comp[not x] (Kosaraju numbers components in
// topological order, so "later" means closer to the sinks). O(n + m).
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    int N = 2 * m + 2;
    vector<vector<int>> g(N), rg(N);
    auto lit = [](char c, int x) { return 2 * x + (c == '-'); };
    for (int i = 0; i < n; i++) {
        char c1, c2;
        int x1, x2;
        cin >> c1 >> x1 >> c2 >> x2;
        int a = lit(c1, x1), b = lit(c2, x2);
        g[a ^ 1].push_back(b), rg[b].push_back(a ^ 1);
        g[b ^ 1].push_back(a), rg[a].push_back(b ^ 1);
    }
    vector<int> order, it(N, 0);
    vector<bool> seen(N, false);
    for (int s = 2; s < N; s++) {           // iterative DFS, record finishing order
        if (seen[s]) continue;
        vector<int> st = {s};
        seen[s] = true;
        while (!st.empty()) {
            int u = st.back();
            if (it[u] < (int)g[u].size()) {
                int v = g[u][it[u]++];
                if (!seen[v]) seen[v] = true, st.push_back(v);
            } else {
                order.push_back(u);
                st.pop_back();
            }
        }
    }
    vector<int> comp(N, 0);
    int k = 0;
    for (int i = (int)order.size() - 1; i >= 0; i--) {
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
    string res;
    for (int x = 1; x <= m; x++) {
        if (comp[2 * x] == comp[2 * x + 1]) return cout << "IMPOSSIBLE\n", 0;
        res += comp[2 * x] > comp[2 * x + 1] ? "+ " : "- ";
    }
    cout << res << "\n";
}
