// CSES: Range Xor Queries
// Prefix xors: p[i] = x1 ^ ... ^ xi. Since y ^ y = 0, xor(a..b) = p[b] ^ p[a-1], exactly
// like prefix sums with subtraction replaced by xor (xor is its own inverse). O(n + q).
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<int> p(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        p[i] = p[i - 1] ^ x;
    }
    while (q--) {
        int a, b;
        cin >> a >> b;
        cout << (p[b] ^ p[a - 1]) << "\n";
    }
}
