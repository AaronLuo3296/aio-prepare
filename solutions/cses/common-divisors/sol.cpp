// CSES: Common Divisors
// Answer = the largest d that divides at least two of the numbers. For each d, count the
// multiples of d present (a harmonic sum again): O(X log X) for X = 1e6.
#include <bits/stdc++.h>
using namespace std;
const int X = 1000000;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> cnt(X + 1, 0);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        cnt[x]++;
    }
    for (int d = X; d >= 1; d--) {
        int multiples = 0;
        for (int m = d; m <= X && multiples < 2; m += d) multiples += cnt[m];
        if (multiples >= 2) {
            cout << d << "\n";
            return 0;
        }
    }
}
