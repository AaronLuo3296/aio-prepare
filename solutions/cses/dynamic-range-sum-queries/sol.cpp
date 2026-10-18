// CSES: Dynamic Range Sum Queries
// Fenwick tree (BIT): node i stores the sum of the (i & -i) elements ending at i. Update and
// prefix query each touch O(log n) nodes. Sums reach 2e5 * 1e9: long long. O((n + q) log n).
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int n;
vector<ll> bit;
void add(int i, ll d) {
    for (; i <= n; i += i & -i) bit[i] += d;
}
ll prefix(int i) {
    ll s = 0;
    for (; i > 0; i -= i & -i) s += bit[i];
    return s;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int q;
    cin >> n >> q;
    bit.assign(n + 1, 0);
    vector<ll> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        add(i, a[i]);
    }
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int k;
            ll u;
            cin >> k >> u;
            add(k, u - a[k]);                  // BIT stores sums, so add the difference
            a[k] = u;
        } else {
            int l, r;
            cin >> l >> r;
            cout << prefix(r) - prefix(l - 1) << "\n";
        }
    }
}
