// Kadane's algorithm with a classic bug: best starts at 0, so an all-negative
// array prints 0 instead of its largest element. Run the stress test to find it:
//   templates/stress/stress.sh templates/stress/buggy_max_subarray.cpp \
//       templates/stress/brute_max_subarray.cpp templates/stress/gen_max_subarray.py
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n;
    cin >> n;
    vector<ll> a(n);
    for (auto& x : a) cin >> x;

    ll best = 0, cur = 0;  // BUG: best should start at a[0] (or LLONG_MIN)
    for (ll x : a) {
        cur = max(x, cur + x);
        best = max(best, cur);
    }
    cout << best << "\n";
}
