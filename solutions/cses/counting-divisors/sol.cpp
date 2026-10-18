// CSES: Counting Divisors
// Sieve-style: for every d, add 1 to each multiple of d. Total work is the sum of X/d,
// a harmonic sum: O(X log X) for X = 1e6, then O(1) per query.
#include <bits/stdc++.h>
using namespace std;
const int X = 1000000;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<int> cnt(X + 1, 0);
    for (int d = 1; d <= X; d++)
        for (int m = d; m <= X; m += d) cnt[m]++;
    int n;
    cin >> n;
    while (n--) {
        int x;
        cin >> x;
        cout << cnt[x] << "\n";
    }
}
