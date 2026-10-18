// CSES: Exponentiation
// Fast exponentiation: a^b = (a^2)^(b/2) * (a if b is odd). One squaring per bit of b:
// O(log b) per query. Reduce mod p after every multiplication (products < 1e18 fit in ll).
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
        ll a, b;
        cin >> a >> b;
        cout << power(a, b, MOD) << "\n";      // power(0, 0) = 1, as the problem requires
    }
}
