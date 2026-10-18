// AtCoder Educational DP Contest: B - Frog 2
// Same as Frog 1 but the last jump has length 1..K. O(N K).
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, k;
    cin >> n >> k;
    vector<int> h(n);
    for (auto& x : h) cin >> x;
    vector<int> cost(n, INT_MAX);
    cost[0] = 0;
    for (int i = 1; i < n; i++)
        for (int j = 1; j <= k && j <= i; j++)
            cost[i] = min(cost[i], cost[i - j] + abs(h[i] - h[i - j]));
    cout << cost[n - 1] << "\n";
}
