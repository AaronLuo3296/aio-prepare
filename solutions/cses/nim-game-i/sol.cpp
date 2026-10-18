// CSES: Nim Game I
// Bouton's theorem: the first player wins iff x_1 xor x_2 xor ... xor x_n != 0. Invariant
// argument: from xor 0 every move makes it nonzero; from nonzero xor there is always a move
// back to 0 (pick a heap containing the highest set bit of the xor). O(n) per test.
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
            x ^= h;
        }
        cout << (x ? "first" : "second") << "\n";
    }
}
