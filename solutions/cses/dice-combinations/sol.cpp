// CSES: Dice Combinations
// ways[s] = ways[s-1] + ... + ways[s-6] (condition on the last throw), ways[0] = 1. O(6n).
#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;

int main() {
    int n;
    cin >> n;
    vector<int> ways(n + 1, 0);
    ways[0] = 1;
    for (int s = 1; s <= n; s++)
        for (int d = 1; d <= 6 && d <= s; d++)
            ways[s] = (ways[s] + ways[s - d]) % MOD;
    cout << ways[n] << "\n";
}
