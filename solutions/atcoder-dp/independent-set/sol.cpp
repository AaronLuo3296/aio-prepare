// AtCoder Educational DP Contest: P - Independent Set
// Tree DP. white[v] / black[v] = colourings of v's subtree with v white / black.
// white[v] = prod over children (white[c] + black[c]); black[v] = prod white[c]. O(N).
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD = 1e9 + 7;

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

    vector<ll> white(n + 1, 1), black(n + 1, 1);
    for (int i = n - 1; i > 0; i--) {
        int v = order[i], p = parent[v];
        white[p] = white[p] * ((white[v] + black[v]) % MOD) % MOD;
        black[p] = black[p] * white[v] % MOD;
    }
    cout << (white[1] + black[1]) % MOD << "\n";
}
