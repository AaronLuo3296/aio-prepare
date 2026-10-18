// CSES: Stair Game
// Staircase nim. Balls on odd stairs do not matter: if the opponent moves balls from an
// odd stair down to an even one, move the same balls down again, back to an odd stair (or
// to stair 1, where they are dead). So the game is plain nim on the even stairs: first
// player wins iff p_2 xor p_4 xor ... != 0.
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
        for (int i = 1; i <= n; i++) {
            int p;
            cin >> p;
            if (i % 2 == 0) x ^= p;
        }
        cout << (x ? "first" : "second") << "\n";
    }
}
