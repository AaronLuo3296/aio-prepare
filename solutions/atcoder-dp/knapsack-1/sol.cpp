// AtCoder Educational DP Contest: D - Knapsack 1
// 0/1 knapsack over weight, iterating w downwards (see Book Shop).
// Values reach 100 * 1e9, so long long. O(N W).
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n, cap;
    cin >> n >> cap;
    vector<ll> best(cap + 1, 0);
    for (int i = 0; i < n; i++) {
        int w;
        ll v;
        cin >> w >> v;
        for (int c = cap; c >= w; c--) best[c] = max(best[c], best[c - w] + v);
    }
    cout << best[cap] << "\n";
}
