// CSES: Factory Machines
// "Can we make t products in time T?" is monotone in T, so binary search T.
// Invariant: lo is always too short, hi is always enough. hi = fastest machine * t <= 1e18.
// Stop summing once we reach t, otherwise the sum can overflow. O(n log(1e18)).
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    ll t;
    cin >> n >> t;
    vector<ll> k(n);
    for (auto& x : k) cin >> x;

    auto enough = [&](ll time) {
        ll made = 0;
        for (ll x : k) {
            made += time / x;
            if (made >= t) return true;
        }
        return false;
    };

    ll lo = 0, hi = *min_element(k.begin(), k.end()) * t;
    while (hi - lo > 1) {
        ll mid = lo + (hi - lo) / 2;
        (enough(mid) ? hi : lo) = mid;
    }
    cout << hi << "\n";
}
