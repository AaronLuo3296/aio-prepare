// CSES: Trailing Zeros
// Legendre: the number of factors 5 in n! is sum of floor(n / 5^k); factors 2 are plentiful.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ll n;
    cin >> n;
    ll zeros = 0;
    for (ll p = 5; p <= n; p *= 5) zeros += n / p;
    cout << zeros << "\n";
}
