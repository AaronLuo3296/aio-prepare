// CSES: Subarray Divisibility
// n | P[r] - P[l]  <=>  P[r] = P[l] (mod n). Count equal residues: the pigeonhole
// lemma "some prefix sums agree mod n" made quantitative. C++ % can be negative, so
// normalise. O(n).
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<ll> seen(n, 0);
    seen[0] = 1;
    ll prefix = 0, count = 0;
    for (int i = 0; i < n; i++) {
        ll a;
        cin >> a;
        prefix = ((prefix + a) % n + n) % n;
        count += seen[prefix]++;
    }
    cout << count << "\n";
}
