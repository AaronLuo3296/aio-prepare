// AtCoder Educational DP Contest: A - Frog 1
// cost[i] = min(cost[i-1] + |h_i - h_{i-1}|, cost[i-2] + |h_i - h_{i-2}|). O(N).
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin >> n;
    vector<int> h(n);
    for (auto& x : h) cin >> x;
    vector<int> cost(n, 0);
    for (int i = 1; i < n; i++) {
        cost[i] = cost[i - 1] + abs(h[i] - h[i - 1]);
        if (i >= 2) cost[i] = min(cost[i], cost[i - 2] + abs(h[i] - h[i - 2]));
    }
    cout << cost[n - 1] << "\n";
}
