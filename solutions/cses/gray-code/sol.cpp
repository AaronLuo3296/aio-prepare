// CSES: Gray Code
// The i-th reflected Gray code is i XOR (i >> 1); consecutive codes differ in one bit. O(n 2^n).
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < (1 << n); i++) {
        int g = i ^ (i >> 1);
        for (int b = n - 1; b >= 0; b--) cout << ((g >> b) & 1);
        cout << "\n";
    }
}
