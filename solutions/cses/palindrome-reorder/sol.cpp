// CSES: Palindrome Reorder
// Possible iff at most one letter has an odd count. Put half of each letter on the left,
// the odd letter (if any) in the middle, then mirror. O(n).
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    string s;
    cin >> s;
    array<int, 26> cnt{};
    for (char c : s) cnt[c - 'A']++;

    int odd = -1;
    for (int c = 0; c < 26; c++) {
        if (cnt[c] % 2 == 1) {
            if (odd != -1) {
                cout << "NO SOLUTION\n";
                return 0;
            }
            odd = c;
        }
    }

    string half;
    for (int c = 0; c < 26; c++) half += string(cnt[c] / 2, char('A' + c));
    string mid = (odd == -1) ? "" : string(1, char('A' + odd));
    string back(half.rbegin(), half.rend());
    cout << half + mid + back << "\n";
}
