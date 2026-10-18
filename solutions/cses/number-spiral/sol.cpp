// CSES: Number Spiral
// Layer z = max(y, x) ends at z^2; the parity of z decides which way the layer runs. O(1).
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll value(ll y, ll x) {
    if (y > x) return (y % 2 == 0) ? y * y - x + 1 : (y - 1) * (y - 1) + x;
    return (x % 2 == 1) ? x * x - y + 1 : (x - 1) * (x - 1) + y;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        ll y, x;
        cin >> y >> x;
        cout << value(y, x) << "\n";
    }
}
