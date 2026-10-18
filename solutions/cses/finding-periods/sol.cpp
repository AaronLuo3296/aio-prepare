// CSES: Finding Periods
// Z-function: z[i] = length of the longest common prefix of s and s[i..]. A prefix of
// length p generates s exactly when s[i] = s[i-p] for all i >= p, i.e. when the suffix at
// p matches the start of s all the way to the end: z[p] == n - p (and p = n always works).
// O(n).
#include <bits/stdc++.h>
using namespace std;
int main() {
    string s;
    cin >> s;
    int n = s.size();
    vector<int> z(n, 0);
    for (int i = 1, l = 0, r = 0; i < n; i++) {    // [l, r) = rightmost match window
        if (i < r) z[i] = min(r - i, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] > r) l = i, r = i + z[i];
    }
    for (int p = 1; p <= n; p++)
        if (p == n || z[p] == n - p) cout << p << " ";
    cout << "\n";
}
