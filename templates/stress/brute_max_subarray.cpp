// Brute force: try every subarray [l, r]. O(n^2), obviously correct.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n;
    cin >> n;
    vector<ll> a(n);
    for (auto& x : a) cin >> x;

    ll best = LLONG_MIN;
    for (int l = 0; l < n; l++) {
        ll sum = 0;
        for (int r = l; r < n; r++) {
            sum += a[r];
            best = max(best, sum);
        }
    }
    cout << best << "\n";
}
