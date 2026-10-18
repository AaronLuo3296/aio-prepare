// CSES: Elevator Rides
// dp[mask] = (fewest rides, smallest weight in the last ride) to carry the people in mask,
// compared lexicographically. Adding person i either fits in the last ride or opens a new
// one. Exchange argument: among optimal ways, keeping the last ride lightest is never worse.
// O(2^n * n).
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long x;
    cin >> n >> x;
    vector<long long> w(n);
    for (auto& v : w) cin >> v;
    vector<pair<int, long long>> dp(1 << n, {n + 1, 0});
    dp[0] = {1, 0};                            // one empty ride already open
    for (int mask = 1; mask < (1 << n); mask++)
        for (int i = 0; i < n; i++) {
            if (!(mask >> i & 1)) continue;
            auto [rides, last] = dp[mask ^ (1 << i)];
            if (last + w[i] <= x) last += w[i];
            else {
                rides++;
                last = w[i];
            }
            dp[mask] = min(dp[mask], make_pair(rides, last));
        }
    cout << dp[(1 << n) - 1].first << "\n";
}
