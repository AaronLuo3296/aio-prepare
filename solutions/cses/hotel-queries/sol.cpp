// CSES: Hotel Queries
// Max segment tree, then "descend": from the root, go left if the left child's max is
// enough, else right. That finds the FIRST hotel with >= r free rooms in O(log n), instead
// of binary search over prefix maxima (O(log^2 n)). The tree size is a power of two so
// that node 1 is the root of a perfect tree; padding leaves are 0.
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    int sz = 1;
    while (sz < n) sz *= 2;
    vector<int> t(2 * sz, 0);
    for (int i = 0; i < n; i++) cin >> t[sz + i];
    for (int i = sz - 1; i > 0; i--) t[i] = max(t[2 * i], t[2 * i + 1]);
    for (int j = 0; j < m; j++) {
        int r;
        cin >> r;
        int res = 0;
        if (t[1] >= r) {
            int v = 1;
            while (v < sz) v = t[2 * v] >= r ? 2 * v : 2 * v + 1;
            res = v - sz + 1;
            for (t[v] -= r; v > 1; v /= 2) t[v / 2] = max(t[v], t[v ^ 1]);
        }
        cout << res << " \n"[j == m - 1];
    }
}
