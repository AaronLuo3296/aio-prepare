// CSES: Polygon Area
// Shoelace formula: 2 * area = |sum over edges of cross(p_i, p_{i+1})|. Each term can be
// near 2*10^18 and there are 1000 of them, so the running sum overflows long long even
// though the final answer fits: accumulate in __int128.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    int n;
    cin >> n;
    vector<ll> x(n), y(n);
    for (int i = 0; i < n; i++) cin >> x[i] >> y[i];
    __int128 s = 0;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        s += (__int128)x[i] * y[j] - (__int128)x[j] * y[i];
    }
    if (s < 0) s = -s;
    cout << (ll)s << "\n";
}
