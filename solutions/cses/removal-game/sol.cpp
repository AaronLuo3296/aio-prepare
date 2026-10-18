// CSES: Removal Game
// Interval DP on the score difference: d[l][r] = (mover's score) - (opponent's score) on
// x[l..r] = max(x[l] - d[l+1][r], x[r] - d[l][r-1]). First player's score is
// (total + d[0][n-1]) / 2. Iterating r upwards and l downwards needs only one row: O(n^2)
// time, O(n) memory (a full 5000x5000 table of long long would be 200 MB).
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    int n;
    cin >> n;
    vector<ll> x(n);
    ll total = 0;
    for (ll &v : x) cin >> v, total += v;
    vector<ll> d(n);                        // d[l] holds d[l][r] for the current r
    for (int r = 0; r < n; r++) {
        d[r] = x[r];
        for (int l = r - 1; l >= 0; l--)    // d[l+1] is already d[l+1][r]; d[l] is d[l][r-1]
            d[l] = max(x[l] - d[l + 1], x[r] - d[l]);
    }
    cout << (total + d[0]) / 2 << "\n";
}
