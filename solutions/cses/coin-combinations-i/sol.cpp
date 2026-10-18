// CSES: Coin Combinations I
// ORDERED sequences: condition on the LAST coin, ways[s] = sum ways[s - c].
// Sum loop outside, coin loop inside. O(n x).
#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, x;
    cin >> n >> x;
    vector<int> c(n);
    for (auto& v : c) cin >> v;
    vector<int> ways(x + 1, 0);
    ways[0] = 1;
    for (int s = 1; s <= x; s++)
        for (int v : c)
            if (v <= s) ways[s] = (ways[s] + ways[s - v]) % MOD;
    cout << ways[x] << "\n";
}
