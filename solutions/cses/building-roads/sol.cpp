// CSES: Building Roads
// Find the connected components; join the first city of each component to the first
// city of the next one. k components need exactly k - 1 new roads. O(n + m).
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<bool> seen(n + 1, false);
    vector<int> leaders;
    for (int s = 1; s <= n; s++) {
        if (seen[s]) continue;
        leaders.push_back(s);
        vector<int> stack = {s};                 // iterative DFS
        seen[s] = true;
        while (!stack.empty()) {
            int u = stack.back();
            stack.pop_back();
            for (int v : adj[u])
                if (!seen[v]) {
                    seen[v] = true;
                    stack.push_back(v);
                }
        }
    }
    cout << leaders.size() - 1 << "\n";
    for (size_t i = 1; i < leaders.size(); i++)
        cout << leaders[i - 1] << " " << leaders[i] << "\n";
}
