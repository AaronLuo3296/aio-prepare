// CSES: Finding Borders
// The borders of s are exactly pi[n-1], pi[pi[n-1]-1], ... (a border of a border is a
// border, and the prefix function gives the longest one). Collect the chain and print it
// in increasing order. O(n).
#include <bits/stdc++.h>
using namespace std;
int main() {
    string s;
    cin >> s;
    int n = s.size();
    vector<int> pi(n, 0);
    for (int i = 1; i < n; i++) {
        int k = pi[i - 1];
        while (k > 0 && s[i] != s[k]) k = pi[k - 1];
        if (s[i] == s[k]) k++;
        pi[i] = k;
    }
    vector<int> res;
    for (int k = pi[n - 1]; k > 0; k = pi[k - 1]) res.push_back(k);
    reverse(res.begin(), res.end());
    for (int k : res) cout << k << " ";
    cout << "\n";
}
