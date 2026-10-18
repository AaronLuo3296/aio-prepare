#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    int n;
    cin >> n;
    vector<ll> a(n);
    for (auto& x : a) cin >> x;
    ll best = a[0], cur = 0;
    for (ll x : a) {
        cur = max(x, cur + x);
        best = max(best, cur);
    }
    cout << best << "\n";
}
