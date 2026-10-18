// CSES: Binomial Coefficients
// C(a, b) = a! / (b! (a-b)!). Precompute factorials mod p, then ONE inverse
// inv_fact[N] = fact[N]^(p-2) (Fermat) and walk down: inv_fact[i-1] = inv_fact[i] * i.
// O(N + log p) precomputation, O(1) per query.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD = 1e9 + 7;
const int N = 1000000;
ll power(ll a, ll b) {
    ll r = 1;
    for (a %= MOD; b > 0; b >>= 1) {
        if (b & 1) r = r * a % MOD;
        a = a * a % MOD;
    }
    return r;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<ll> fact(N + 1), inv_fact(N + 1);
    fact[0] = 1;
    for (int i = 1; i <= N; i++) fact[i] = fact[i - 1] * i % MOD;
    inv_fact[N] = power(fact[N], MOD - 2);
    for (int i = N; i > 0; i--) inv_fact[i - 1] = inv_fact[i] * i % MOD;
    int n;
    cin >> n;
    while (n--) {
        int a, b;
        cin >> a >> b;
        cout << fact[a] * inv_fact[b] % MOD * inv_fact[a - b] % MOD << "\n";
    }
}
