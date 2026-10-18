// CSES: Subarray Sums II
// Same prefix-sum counting as Subarray Sums I. It never relied on positivity,
// so negative values are fine (two pointers would NOT be). O(n log n).
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    ll x;
    cin >> n >> x;
    map<ll, int> seen;                   // prefix sum -> how many times it occurred
    seen[0] = 1;
    ll prefix = 0, count = 0;
    for (int i = 0; i < n; i++) {
        ll a;
        cin >> a;
        prefix += a;
        auto it = seen.find(prefix - x);
        if (it != seen.end()) count += it->second;
        seen[prefix]++;
    }
    cout << count << "\n";
}
