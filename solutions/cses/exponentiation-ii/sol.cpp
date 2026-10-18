// CSES: Exponentiation II
// Fermat: a^(p-1) = 1 (mod p) when p does not divide a, so exponents live mod p-1:
// a^(b^c) = a^(b^c mod (p-1)). (When a = 0 the reduced exponent is 0 only if b^c = 0 or
// b^c is a multiple of p-1 = 2 * 500000003, which needs b >= p-1 > 1e9. So it is safe.)
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD = 1e9 + 7;
ll power(ll a, ll b, ll m) {
    ll r = 1 % m;
    a %= m;
    for (; b > 0; b >>= 1) {
        if (b & 1) r = r * a % m;
        a = a * a % m;
    }
    return r;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    while (n--) {
        ll a, b, c;
        cin >> a >> b >> c;
        cout << power(a, power(b, c, MOD - 1), MOD) << "\n";
    }
}
