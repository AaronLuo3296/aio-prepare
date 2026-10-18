// CSES: Coin Combinations II
// UNORDERED multisets: decide coin types one at a time. After the outer loop has
// processed coins c_1..c_i, ways[s] counts multisets using only those coins.
// Coin loop outside, sum loop inside. O(n x).
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
    for (int v : c)
        for (int s = v; s <= x; s++)
            ways[s] = (ways[s] + ways[s - v]) % MOD;
    cout << ways[x] << "\n";
}
