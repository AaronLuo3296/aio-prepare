// CSES: Edit Distance
// d[i][j] = distance between the first i chars of a and first j chars of b:
// min(d[i-1][j] + 1, d[i][j-1] + 1, d[i-1][j-1] + (a_i != b_j)).
// Row i only needs row i-1, so keep two rows: O(nm) time, O(m) memory.
#include <bits/stdc++.h>
using namespace std;
int main() {
    string a, b;
    cin >> a >> b;
    int n = a.size(), m = b.size();
    vector<int> prev(m + 1), cur(m + 1);
    iota(prev.begin(), prev.end(), 0);   // d[0][j] = j
    for (int i = 1; i <= n; i++) {
        cur[0] = i;
        for (int j = 1; j <= m; j++)
            cur[j] = min({prev[j] + 1, cur[j - 1] + 1,
                          prev[j - 1] + (a[i - 1] != b[j - 1])});
        swap(prev, cur);
    }
    cout << prev[m] << "\n";
}
