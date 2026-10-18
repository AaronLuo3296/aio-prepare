// CSES: Array Description
// ways[v] = number of valid prefixes ending in value v. Each new position takes
// v from v-1, v, v+1 of the previous position, restricted to x_i when x_i != 0. O(n m).
#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> x(n);
    for (auto& v : x) cin >> v;

    vector<long long> ways(m + 2, 0);    // indices 0 and m+1 stay 0 as sentinels
    for (int v = 1; v <= m; v++) ways[v] = (x[0] == 0 || x[0] == v);
    for (int i = 1; i < n; i++) {
        vector<long long> next(m + 2, 0);
        for (int v = 1; v <= m; v++)
            if (x[i] == 0 || x[i] == v)
                next[v] = (ways[v - 1] + ways[v] + ways[v + 1]) % MOD;
        ways = next;
    }
    long long total = 0;
    for (int v = 1; v <= m; v++) total += ways[v];
    cout << total % MOD << "\n";
}
