// CSES: Missing Number
// The answer is 1 + 2 + ... + n minus the sum of the given numbers. O(n).
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ll n;
    cin >> n;
    ll sum = n * (n + 1) / 2;
    for (int i = 0; i < n - 1; i++) {
        ll x;
        cin >> x;
        sum -= x;
    }
    cout << sum << "\n";
}
