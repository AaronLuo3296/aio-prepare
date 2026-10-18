// CSES: Monster Game I
// dp[i] = least time to reach and kill monster i = min over the previous kill j (j = 0:
// none yet, skill f_0 = x) of dp[j] + s_i * f_j. Each j is a line y = f_j * s + dp[j];
// slopes f_j do not increase and queries s_i do not decrease, so a monotone convex hull
// trick answers all n queries in O(n) total.
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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    ll x;
    cin >> n >> x;
    vector<ll> s(n), f(n);
    for (ll &v : s) cin >> v;
    for (ll &v : f) cin >> v;
    MonotoneCHT cht;
    cht.add(x, 0);
    ll dp = 0;
    for (int i = 0; i < n; i++) {
        dp = cht.query(s[i]);
        cht.add(f[i], dp);
    }
    cout << dp << "\n";
}
