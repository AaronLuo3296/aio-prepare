// CSES: Nim Game II
// Subtraction game with moves {1, 2, 3}: a single heap of x has Grundy value x mod 4
// (mex of the previous three values cycles 0,1,2,3). Sprague-Grundy: the sum of games has
// Grundy value = xor of the parts, so the first player wins iff xor of (x_i mod 4) != 0.
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n, x = 0;
        cin >> n;
        for (int i = 0; i < n; i++) {
            int h;
            cin >> h;
            x ^= h % 4;
        }
        cout << (x ? "first" : "second") << "\n";
    }
}
