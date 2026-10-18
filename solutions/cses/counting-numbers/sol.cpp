// CSES: Counting Numbers
// Digit DP. f(x) = how many v in [0, x] have no two equal adjacent digits; the answer is
// f(b) - f(a-1). Walk the digits of x from the left. At position i, choosing a digit
// smaller than x's digit frees every later position: each can be any of 9 digits (anything
// but its left neighbour). Numbers shorter than x are counted separately (9 * 9^(len-1)).
// O(18 * 10).
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll f(ll x) {                                // count in [0, x]
    if (x < 10) return x + 1;               // 0..x, all single digits (f(-1) = 0)
    string s = to_string(x);
    int L = s.size();
    vector<ll> p9(L + 1, 1);
    for (int i = 1; i <= L; i++) p9[i] = p9[i - 1] * 9;
    ll res = 1;                             // the number 0
    for (int len = 1; len < L; len++) res += 9 * p9[len - 1];
    for (int i = 0; i < L; i++) {
        int d = s[i] - '0';
        for (int c = (i == 0 ? 1 : 0); c < d; c++)
            if (i == 0 || c != s[i - 1] - '0') res += p9[L - 1 - i];
        if (i > 0 && s[i] == s[i - 1]) return res;   // x's own prefix already fails
    }
    return res + 1;                         // x itself is valid
}

int main() {
    ll a, b;
    cin >> a >> b;
    cout << f(b) - f(a - 1) << "\n";
}
