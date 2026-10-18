// CSES: Range Update Queries
// Store the difference array d[i] = a[i] - a[i-1] in a Fenwick tree. "Add u to [a, b]" is
// d[a] += u, d[b+1] -= u; the value at k is the prefix sum d[1] + ... + d[k]. Values reach
// 2*10^5 * 10^9, so long long. O((n + q) log n).
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int n;
vector<ll> t;
void add(int i, ll v) {
    for (; i <= n; i += i & -i) t[i] += v;
}
ll prefix(int i) {
    ll s = 0;
    for (; i > 0; i -= i & -i) s += t[i];
    return s;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int q;
    cin >> n >> q;
    t.assign(n + 2, 0);
    for (int i = 1; i <= n; i++) {
        ll x;
        cin >> x;
        add(i, x), add(i + 1, -x);
    }
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int a, b;
            ll u;
            cin >> a >> b >> u;
            add(a, u), add(b + 1, -u);
        } else {
            int k;
            cin >> k;
            cout << prefix(k) << "\n";
        }
    }
}
