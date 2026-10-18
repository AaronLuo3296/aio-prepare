// CSES: Weird Algorithm
// Simulate the Collatz map. Values exceed 2^31 for some n <= 10^6, so use long long.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ll n;
    cin >> n;
    cout << n;
    while (n != 1) {
        n = (n % 2 == 0) ? n / 2 : 3 * n + 1;
        cout << " " << n;
    }
    cout << "\n";
}
