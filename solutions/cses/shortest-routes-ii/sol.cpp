// CSES: Shortest Routes II
// n <= 500 and many queries: Floyd-Warshall. After round k, d[i][j] is the shortest path
// using only intermediate vertices 1..k (induction on k). O(n^3 + q).
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, q;
    cin >> n >> m >> q;
    const ll INF = LLONG_MAX / 4;                // INF + INF must not overflow
    vector<vector<ll>> d(n + 1, vector<ll>(n + 1, INF));
    for (int i = 1; i <= n; i++) d[i][i] = 0;
    for (int i = 0; i < m; i++) {
        int a, b;
        ll c;
        cin >> a >> b >> c;
        d[a][b] = d[b][a] = min(d[a][b], c);     // keep the cheapest parallel road
    }
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
    while (q--) {
        int a, b;
        cin >> a >> b;
        cout << (d[a][b] >= INF ? -1 : d[a][b]) << "\n";
    }
}
