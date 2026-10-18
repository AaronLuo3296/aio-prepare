// CSES: Subarray Squares
// dp[j][i] = min cost to split the first i elements into j parts
//          = min_{p < i} dp[j-1][p] + (P[i] - P[p])^2, with prefix sums P.
// The best split point opt(i) is non-decreasing in i (the cost satisfies the quadrangle
// inequality), so divide and conquer: solve the middle i by scanning [optl, optr], then
// the left half only needs [optl, opt(mid)] and the right half [opt(mid), optr].
// O(k n log n).
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
vector<ll> P, prv, cur;

void solve(int l, int r, int optl, int optr) {      // fill cur[l..r]
    if (l > r) return;
    int mid = (l + r) / 2, best = optl;
    cur[mid] = LLONG_MAX;
    for (int p = optl; p <= min(mid - 1, optr); p++) {
        if (prv[p] == LLONG_MAX) continue;
        ll v = prv[p] + (P[mid] - P[p]) * (P[mid] - P[p]);
        if (v < cur[mid]) cur[mid] = v, best = p;
    }
    solve(l, mid - 1, optl, best);
    solve(mid + 1, r, best, optr);
}

int main() {
    int n, k;
    cin >> n >> k;
    P.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) cin >> P[i], P[i] += P[i - 1];
    prv.assign(n + 1, LLONG_MAX);
    prv[0] = 0;                             // zero parts cover zero elements
    cur.assign(n + 1, LLONG_MAX);
    for (int j = 1; j <= k; j++) {
        fill(cur.begin(), cur.end(), LLONG_MAX);
        solve(1, n, 0, n - 1);
        swap(prv, cur);
    }
    cout << prv[n] << "\n";
}
