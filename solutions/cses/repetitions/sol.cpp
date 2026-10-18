// CSES: Repetitions
// Scan once, tracking the length of the current run of equal characters. O(n).
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    string s;
    cin >> s;
    int best = 1, run = 1;
    for (size_t i = 1; i < s.size(); i++) {
        run = (s[i] == s[i - 1]) ? run + 1 : 1;
        best = max(best, run);
    }
    cout << best << "\n";
}
