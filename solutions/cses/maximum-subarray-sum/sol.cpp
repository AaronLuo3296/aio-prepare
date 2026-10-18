// CSES: Maximum Subarray Sum
// Kadane: best sum of a subarray ENDING at i is max(a_i, best ending at i-1 plus a_i).
// Induction on i. The answer must be non-empty, so all-negative arrays give the max element.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    ll endingHere = 0, best = LLONG_MIN;
    for (int i = 0; i < n; i++) {
        ll a;
        cin >> a;
        endingHere = (i == 0) ? a : max(a, endingHere + a);
        best = max(best, endingHere);
    }
    cout << best << "\n";
}
