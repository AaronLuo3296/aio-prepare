// CSES: Apple Division
// n <= 20, so try all 2^n ways to split: bit i of mask says which group apple i joins.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n;
    cin >> n;
    vector<ll> p(n);
    for (auto& x : p) cin >> x;
    ll total = accumulate(p.begin(), p.end(), 0LL);

    ll best = LLONG_MAX;
    for (int mask = 0; mask < (1 << n); mask++) {
        ll group = 0;
        for (int i = 0; i < n; i++)
            if (mask >> i & 1) group += p[i];
        best = min(best, llabs(total - 2 * group));
    }
    cout << best << "\n";
}
