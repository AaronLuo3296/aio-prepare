// CSES: Static Range Minimum Queries
// Sparse table: sp[j][i] = min of the 2^j elements starting at i. A query [a, b] is covered
// by two overlapping blocks of length 2^k (k = floor(log2(len))); min is idempotent, so the
// overlap does no harm. O(n log n) build, O(1) per query.
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    int LOG = 1;
    while ((1 << LOG) <= n) LOG++;
    vector<vector<int>> sp(LOG, vector<int>(n));
    for (auto& x : sp[0]) cin >> x;
    for (int j = 1; j < LOG; j++)
        for (int i = 0; i + (1 << j) <= n; i++)
            sp[j][i] = min(sp[j - 1][i], sp[j - 1][i + (1 << (j - 1))]);
    while (q--) {
        int a, b;
        cin >> a >> b;
        a--;                                   // half-open [a, b)
        int k = 31 - __builtin_clz(b - a);     // floor(log2(len))
        cout << min(sp[k][a], sp[k][b - (1 << k)]) << "\n";
    }
}
