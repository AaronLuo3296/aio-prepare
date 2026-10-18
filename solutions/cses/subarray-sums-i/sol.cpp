// CSES: Subarray Sums I
// A subarray (l, r] has sum P[r] - P[l]. For each r count earlier prefixes equal to
// P[r] - x. O(n log n). (Since all values are positive, two pointers also works: Day 11.)
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
