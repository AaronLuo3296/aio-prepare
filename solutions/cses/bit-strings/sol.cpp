// CSES: Bit Strings
// 2^n mod (10^9 + 7), multiplying step by step and reducing each time. O(n).
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll MOD = 1'000'000'007;

int main() {
    int n;
    cin >> n;
    ll ans = 1;
    for (int i = 0; i < n; i++) ans = ans * 2 % MOD;
    cout << ans << "\n";
}
