// CSES: String Matching
// Prefix function of p + '#' + t: pi[i] = length of the longest proper border of the first
// i+1 characters. '#' occurs in neither string, so pi[i] <= |p|, and pi[i] == |p| exactly
// where an occurrence of p ends. O(n + m).
#include <bits/stdc++.h>
using namespace std;

vector<int> prefix_function(const string &s) {
    vector<int> pi(s.size(), 0);
    for (int i = 1; i < (int)s.size(); i++) {
        int k = pi[i - 1];
        while (k > 0 && s[i] != s[k]) k = pi[k - 1];   // fall back to a shorter border
        if (s[i] == s[k]) k++;
        pi[i] = k;
    }
    return pi;
}

int main() {
    string t, p;
    cin >> t >> p;
    vector<int> pi = prefix_function(p + '#' + t);
    cout << count(pi.begin(), pi.end(), (int)p.size()) << "\n";
}
