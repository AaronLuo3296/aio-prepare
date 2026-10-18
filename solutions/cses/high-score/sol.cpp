// CSES: High Score
// Longest path = shortest path with negated weights, so Bellman-Ford. Run n-1 rounds,
// then n more: any node still improving lies on, or after, a positive cycle. The answer is
// -1 only if such a node can also reach n (and is reachable from 1, which relaxation
// already guarantees). O(n * m).
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    int n, m;
    cin >> n >> m;
    vector<array<ll, 3>> e(m);
    vector<vector<int>> radj(n + 1);
    for (auto &[a, b, x] : e) cin >> a >> b >> x, radj[b].push_back(a);
    const ll NEG = LLONG_MIN / 4;
    vector<ll> d(n + 1, NEG);
    d[1] = 0;
    for (int i = 0; i < n - 1; i++)
        for (auto [a, b, x] : e)
            if (d[a] != NEG && d[a] + x > d[b]) d[b] = d[a] + x;
    vector<bool> inf(n + 1, false);         // improvable forever
    for (int i = 0; i < n; i++)
        for (auto [a, b, x] : e)
            if (d[a] != NEG && (d[a] + x > d[b] || inf[a])) d[b] = max(d[b], d[a] + x), inf[b] = true;
    vector<bool> toN(n + 1, false);         // nodes that can reach n
    vector<int> st = {n};
    toN[n] = true;
    while (!st.empty()) {
        int u = st.back();
        st.pop_back();
        for (int v : radj[u])
            if (!toN[v]) toN[v] = true, st.push_back(v);
    }
    for (int v = 1; v <= n; v++)
        if (inf[v] && toN[v]) return cout << -1 << "\n", 0;
    cout << d[n] << "\n";
}
