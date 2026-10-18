// CSES: Two Knights
// C(k^2, 2) placements minus attacking pairs. Each attacking pair spans a 2x3 or 3x2
// box, and each box holds 2 attacking pairs: 2 * 2 * (k-1)(k-2) = 4(k-1)(k-2). O(n).
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ll n;
    cin >> n;
    for (ll k = 1; k <= n; k++) {
        ll total = k * k * (k * k - 1) / 2;
        ll attacking = 4 * (k - 1) * (k - 2);
        cout << total - attacking << "\n";
    }
}
