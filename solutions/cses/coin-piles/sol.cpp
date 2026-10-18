// CSES: Coin Piles
// Each move removes 3 coins, and neither pile may exceed twice the other (invariant:
// a <= 2b and b <= 2a must hold before every move). Both conditions are also sufficient.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int t;
    cin >> t;
    while (t--) {
        ll a, b;
        cin >> a >> b;
        bool ok = (a + b) % 3 == 0 && a <= 2 * b && b <= 2 * a;
        cout << (ok ? "YES" : "NO") << "\n";
    }
}
