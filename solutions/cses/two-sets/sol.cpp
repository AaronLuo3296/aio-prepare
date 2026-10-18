// CSES: Two Sets
// Need n(n+1)/2 even. Then greedily take the largest numbers that still fit into
// target = n(n+1)/4; every value 0..n(n+1)/2 is a subset sum of {1..n}, so it always works.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ll n;
    cin >> n;
    ll total = n * (n + 1) / 2;
    if (total % 2 != 0) {
        cout << "NO\n";
        return 0;
    }
    ll target = total / 2;
    vector<ll> first, second;
    for (ll i = n; i >= 1; i--) {
        if (i <= target) {
            first.push_back(i);
            target -= i;
        } else {
            second.push_back(i);
        }
    }
    cout << "YES\n" << first.size() << "\n";
    for (ll x : first) cout << x << " ";
    cout << "\n" << second.size() << "\n";
    for (ll x : second) cout << x << " ";
    cout << "\n";
}
