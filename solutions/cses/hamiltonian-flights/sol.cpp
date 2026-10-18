// CSES: Hamiltonian Flights
// dp[mask][v] = number of routes that start at city 0, visit exactly the cities in mask, and
// end at v. Extend by one flight v -> u with u not in mask. Repeated flights count separately,
// so store edge multiplicities. 2^n * n states, n transitions each: O(2^n * n^2), about
// 4e8 cheap steps for n = 20 (fewer, since we skip masks without city 0 or with city n-1 early).
#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;
int dp[1 << 20][20];                           // 80 MB: global, not on the stack
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> in(n);                 // in[u] = list of v with a flight v -> u
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        in[b - 1].push_back(a - 1);
    }
    int full = (1 << n) - 1;
    dp[1][0] = 1;
    for (int mask = 1; mask <= full; mask++) {
        if (!(mask & 1)) continue;             // every route starts at city 0
        if ((mask >> (n - 1) & 1) && mask != full) continue;  // city n-1 must come last
        for (int u = 0; u < n; u++) {
            if (!(mask >> u & 1) || (mask == 1 && u == 0)) continue;
            int prev = mask ^ (1 << u);
            long long ways = 0;
            for (int v : in[u])
                if (prev >> v & 1) ways += dp[prev][v];
            dp[mask][u] = ways % MOD;
        }
    }
    cout << dp[full][n - 1] << "\n";
}
