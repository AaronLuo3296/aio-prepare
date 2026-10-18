// CSES: Stick Lengths
// sum |p_i - c| is minimised by any median c: moving c past the median adds more
// terms than it removes. Sum is up to 2e5 * 1e9, so long long. O(n log n).
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<ll> p(n);
    for (auto& x : p) cin >> x;
    sort(p.begin(), p.end());
    ll median = p[n / 2], cost = 0;
    for (ll x : p) cost += llabs(x - median);
    cout << cost << "\n";
}
