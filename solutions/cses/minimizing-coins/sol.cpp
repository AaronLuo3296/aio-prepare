// CSES: Minimizing Coins
// best[s] = 1 + min over coins c <= s of best[s - c]; best[0] = 0. O(n x).
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, x;
    cin >> n >> x;
    vector<int> c(n);
    for (auto& v : c) cin >> v;
    const int INF = 1e9;
    vector<int> best(x + 1, INF);
    best[0] = 0;
    for (int s = 1; s <= x; s++)
        for (int v : c)
            if (v <= s && best[s - v] != INF)
                best[s] = min(best[s], best[s - v] + 1);
    cout << (best[x] == INF ? -1 : best[x]) << "\n";
}
