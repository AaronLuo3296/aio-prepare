// AtCoder Educational DP O: Matching
// dp[mask] = number of ways to pair men 0..k-1 (k = popcount(mask)) with exactly the women in
// mask. Man k picks a compatible woman not in mask. O(2^n * n).
#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<vector<int>> a(n, vector<int>(n));
    for (auto& row : a)
        for (auto& v : row) cin >> v;
    vector<int> dp(1 << n, 0);
    dp[0] = 1;
    for (int mask = 0; mask < (1 << n); mask++) {
        if (dp[mask] == 0) continue;
        int k = __builtin_popcount(mask);
        if (k == n) continue;
        for (int w = 0; w < n; w++)
            if (a[k][w] && !(mask >> w & 1))
                dp[mask | 1 << w] = (dp[mask | 1 << w] + dp[mask]) % MOD;
    }
    cout << dp[(1 << n) - 1] << "\n";
}
