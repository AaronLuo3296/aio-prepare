// CSES: Increasing Array
// Greedy: raise each element only to the running maximum. Total can reach ~2*10^5 * 10^9.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n;
    cin >> n;
    ll mx = 0, moves = 0;
    for (int i = 0; i < n; i++) {
        ll x;
        cin >> x;
        if (x < mx) moves += mx - x;
        else mx = x;
    }
    cout << moves << "\n";
}
