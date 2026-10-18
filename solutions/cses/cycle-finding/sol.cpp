// CSES: Cycle Finding
// Bellman-Ford from a virtual source (every d starts at 0). If round n still relaxes some
// edge into x, a negative cycle exists. Following parent pointers n times from x lands
// inside the cycle; walk parents again until returning to that node, then reverse.
// O(n * m).
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    int n, m;
    cin >> n >> m;
    vector<array<ll, 3>> e(m);
    for (auto &[a, b, c] : e) cin >> a >> b >> c;
    vector<ll> d(n + 1, 0);
    vector<int> par(n + 1, 0);
    int x = 0;
    for (int i = 0; i < n; i++) {
        x = 0;
        for (auto [a, b, c] : e)
            if (d[a] + c < d[b]) d[b] = d[a] + c, par[b] = a, x = b;
    }
    if (x == 0) return cout << "NO\n", 0;
    for (int i = 0; i < n; i++) x = par[x];
    vector<int> cyc = {x};
    for (int v = par[x]; v != x; v = par[v]) cyc.push_back(v);
    cyc.push_back(x);
    reverse(cyc.begin(), cyc.end());
    cout << "YES\n";
    for (int i = 0; i < (int)cyc.size(); i++) cout << cyc[i] << " \n"[i + 1 == (int)cyc.size()];
}
