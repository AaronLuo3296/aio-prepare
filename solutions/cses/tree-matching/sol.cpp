// CSES: Tree Matching
// Greedy from the leaves up: if a vertex and its parent are both unmatched, match them.
// Exchange argument: some maximum matching uses the edge from a leaf to its parent. O(n).
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
    // BFS from the root gives an order where every parent comes before its children.
    // Walking it backwards processes children before parents (no recursion needed).
    vector<int> order = {1}, parent(n + 1, 0);
    parent[1] = -1;
    for (size_t i = 0; i < order.size(); i++)
        for (int v : adj[order[i]])
            if (v != parent[order[i]]) {
                parent[v] = order[i];
                order.push_back(v);
            }

    vector<bool> matched(n + 1, false);
    int pairs = 0;
    for (int i = n - 1; i > 0; i--) {            // skip order[0], the root
        int v = order[i], p = parent[v];
        if (!matched[v] && !matched[p]) {
            matched[v] = matched[p] = true;
            pairs++;
        }
    }
    cout << pairs << "\n";
}
