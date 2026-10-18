// CSES: Dynamic Range Minimum Queries
// Bottom-up segment tree: leaves at t[n..2n-1], node i = min(t[2i], t[2i+1]). Update walks
// up from a leaf; a query on [l, r) climbs from both ends, taking a node whenever it is a
// right child on the left side (or left child on the right side). O(log n) each.
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<int> t(2 * n);
    for (int i = 0; i < n; i++) cin >> t[n + i];
    for (int i = n - 1; i > 0; i--) t[i] = min(t[2 * i], t[2 * i + 1]);
    while (q--) {
        int type, a, b;
        cin >> type >> a >> b;
        if (type == 1) {
            int i = n + a - 1;
            for (t[i] = b; i > 1; i /= 2) t[i / 2] = min(t[i], t[i ^ 1]);
        } else {
            int res = INT_MAX;
            for (int l = n + a - 1, r = n + b; l < r; l /= 2, r /= 2) {
                if (l & 1) res = min(res, t[l++]);
                if (r & 1) res = min(res, t[--r]);
            }
            cout << res << "\n";
        }
    }
}
