// AtCoder Educational DP Contest Z: Frog 3
// dp[i] = min_j dp[j] + (h_i - h_j)^2 + C = h_i^2 + C + min_j (-2 h_j * h_i + dp[j] + h_j^2).
// The min is over lines with slope -2 h_j (decreasing, since h increases) evaluated at
// x = h_i (increasing): a monotone convex hull trick, O(n) after the O(n^2) DP idea.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Lines y = m*x + b for MINIMUM queries. Slopes must be added in decreasing order and
// queries must come in increasing x; then each line enters and leaves the deque once.
struct MonotoneCHT {
    vector<ll> M, B;
    size_t ptr = 0;
    // l2 is useless if l1 and l3 meet at or left of where l1 and l2 meet. Cross-multiplied
    // in __int128: (b3-b1)*(m1-m2) can reach 10^17 * 10^6, beyond long long.
    bool useless(int i, int j, ll m3, ll b3) {
        return (__int128)(b3 - B[i]) * (M[i] - M[j]) <= (__int128)(B[j] - B[i]) * (M[i] - m3);
    }
    void add(ll m, ll b) {
        if (!M.empty() && M.back() == m) {  // equal slopes: keep the lower line
            if (B.back() <= b) return;
            M.pop_back(), B.pop_back();
        }
        while (M.size() >= 2 && useless(M.size() - 2, M.size() - 1, m, b)) M.pop_back(), B.pop_back();
        M.push_back(m), B.push_back(b);
        ptr = min(ptr, M.size() - 1);
    }
    ll query(ll x) {
        while (ptr + 1 < M.size() && M[ptr + 1] * x + B[ptr + 1] <= M[ptr] * x + B[ptr]) ptr++;
        return M[ptr] * x + B[ptr];
    }
};

int main() {
    int n;
    ll C;
    cin >> n >> C;
    vector<ll> h(n);
    for (ll &x : h) cin >> x;
    MonotoneCHT cht;
    ll dp = 0;                              // dp[0]
    cht.add(-2 * h[0], h[0] * h[0]);
    for (int i = 1; i < n; i++) {
        dp = cht.query(h[i]) + h[i] * h[i] + C;
        cht.add(-2 * h[i], dp + h[i] * h[i]);
    }
    cout << dp << "\n";
}
