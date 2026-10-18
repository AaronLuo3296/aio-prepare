// CSES: Distinct Values Queries
// Mo's algorithm (offline). Sort queries by (block of l, r), with r descending in odd
// blocks so the right pointer sweeps back and forth instead of resetting. Keep cnt[value]
// and the number of values with cnt > 0 while moving the window one step at a time. With
// block size B = n / sqrt(q): O((n + q) sqrt n) steps. Values are compressed to 0..n-1 so
// cnt fits in an array.
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int &x : a) cin >> x;
    vector<int> vals = a;
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    for (int &x : a) x = lower_bound(vals.begin(), vals.end(), x) - vals.begin();
    vector<array<int, 3>> qs(q);
    for (int i = 0; i < q; i++) cin >> qs[i][0] >> qs[i][1], qs[i][0]--, qs[i][1]--, qs[i][2] = i;
    int B = max(1, (int)(n / sqrt((double)q)));
    sort(qs.begin(), qs.end(), [&](const array<int, 3> &x, const array<int, 3> &y) {
        int bx = x[0] / B, by = y[0] / B;
        if (bx != by) return bx < by;
        return (bx & 1) ? x[1] > y[1] : x[1] < y[1];
    });
    vector<int> cnt(n, 0), ans(q);
    int distinct = 0, L = 0, R = -1;        // current window a[L..R], empty at start
    auto add = [&](int i) { distinct += cnt[a[i]]++ == 0; };
    auto remove = [&](int i) { distinct -= --cnt[a[i]] == 0; };
    for (auto [l, r, id] : qs) {
        while (R < r) add(++R);             // grow before shrinking keeps L <= R + 1
        while (L > l) add(--L);
        while (R > r) remove(R--);
        while (L < l) remove(L++);
        ans[id] = distinct;
    }
    for (int x : ans) cout << x << "\n";
}
