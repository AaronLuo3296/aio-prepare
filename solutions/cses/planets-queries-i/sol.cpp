// CSES: Planets Queries I
// Binary lifting on a functional graph: up[j][x] = planet after 2^j teleports, built by
// up[j][x] = up[j-1][up[j-1][x]]. Answer a query by taking the jumps for the set bits of k
// (k < 2^30). O((n + q) log k).
#include <bits/stdc++.h>
using namespace std;
const int LOG = 30;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<array<int, LOG>> up(n + 1);
    for (int i = 1; i <= n; i++) cin >> up[i][0];
    for (int j = 1; j < LOG; j++)
        for (int i = 1; i <= n; i++) up[i][j] = up[up[i][j - 1]][j - 1];
    while (q--) {
        int x, k;
        cin >> x >> k;
        for (int j = 0; j < LOG; j++)
            if (k >> j & 1) x = up[x][j];
        cout << x << "\n";
    }
}
