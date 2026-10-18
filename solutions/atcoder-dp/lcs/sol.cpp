// AtCoder Educational DP Contest: F - LCS
// L[i][j] = LCS length of s[0..i) and t[0..j). Then walk back from (n, m) to
// recover one optimal string. O(nm).
#include <bits/stdc++.h>
using namespace std;
int main() {
    string s, t;
    cin >> s >> t;
    int n = s.size(), m = t.size();
    vector<vector<int>> L(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            L[i][j] = (s[i - 1] == t[j - 1]) ? L[i - 1][j - 1] + 1
                                              : max(L[i - 1][j], L[i][j - 1]);

    string out;
    for (int i = n, j = m; i > 0 && j > 0;) {
        if (s[i - 1] == t[j - 1]) {
            out += s[i - 1];
            i--, j--;
        } else if (L[i - 1][j] >= L[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }
    reverse(out.begin(), out.end());
    cout << out << "\n";
}
