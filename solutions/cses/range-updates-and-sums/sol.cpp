// CSES: Range Updates and Sums
// Lazy segment tree with two pending tags per node: "set to s" (if any) then "add a".
// Composition: a new set wipes both old tags; a new add adds to the add tag. Applying tags
// to a node covering len elements: sum = s*len (if set) + a*len. push() hands the tags to
// the children before descending. O((n + q) log n).
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct LazySeg {
    int n;
    vector<ll> sum, setv, addv;
    vector<bool> has_set;
    LazySeg(const vector<ll> &a) : n(a.size()), sum(4 * n), setv(4 * n), addv(4 * n), has_set(4 * n) {
        build(1, 0, n - 1, a);
    }
    void build(int v, int l, int r, const vector<ll> &a) {
        if (l == r) return void(sum[v] = a[l]);
        int m = (l + r) / 2;
        build(2 * v, l, m, a), build(2 * v + 1, m + 1, r, a);
        sum[v] = sum[2 * v] + sum[2 * v + 1];
    }
    void apply(int v, int len, bool is_set, ll x) {
        if (is_set) has_set[v] = true, setv[v] = x, addv[v] = 0, sum[v] = x * len;
        else addv[v] += x, sum[v] += x * len;
    }
    void push(int v, int l, int r) {
        int m = (l + r) / 2;
        for (int c : {2 * v, 2 * v + 1}) {
            int len = c == 2 * v ? m - l + 1 : r - m;
            if (has_set[v]) apply(c, len, true, setv[v]);
            if (addv[v]) apply(c, len, false, addv[v]);
        }
        has_set[v] = false, addv[v] = 0;
    }
    void update(int v, int l, int r, int ql, int qr, bool is_set, ll x) {
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) return apply(v, r - l + 1, is_set, x);
        push(v, l, r);
        int m = (l + r) / 2;
        update(2 * v, l, m, ql, qr, is_set, x), update(2 * v + 1, m + 1, r, ql, qr, is_set, x);
        sum[v] = sum[2 * v] + sum[2 * v + 1];
    }
    ll query(int v, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return sum[v];
        push(v, l, r);
        int m = (l + r) / 2;
        return query(2 * v, l, m, ql, qr) + query(2 * v + 1, m + 1, r, ql, qr);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<ll> a(n);
    for (ll &x : a) cin >> x;
    LazySeg st(a);
    while (q--) {
        int type, l, r;
        cin >> type >> l >> r;
        if (type == 3) {
            cout << st.query(1, 0, n - 1, l - 1, r - 1) << "\n";
        } else {
            ll x;
            cin >> x;
            st.update(1, 0, n - 1, l - 1, r - 1, type == 2, x);
        }
    }
}
