// CSES: Company Queries I
// Binary lifting: up[j][v] = the 2^j-th boss of v (0 = none). Write k in binary and jump one
// power of two per set bit, like fast exponentiation. O(n log n) build, O(log n) per query.
#include <bits/stdc++.h>
using namespace std;
const int LOG = 18;                            // 2^18 > 2e5
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<array<int, LOG>> up(n + 1);
    up[0].fill(0);                             // vertex 0 = "no boss", absorbs every jump
    up[1].fill(0);
    for (int i = 2; i <= n; i++) cin >> up[i][0];
    for (int j = 1; j < LOG; j++)
        for (int v = 1; v <= n; v++) up[v][j] = up[up[v][j - 1]][j - 1];
    while (q--) {
        int x, k;
        cin >> x >> k;
        for (int j = 0; j < LOG && x != 0; j++)
            if (k >> j & 1) x = up[x][j];
        cout << (x == 0 ? -1 : x) << "\n";
    }
}
