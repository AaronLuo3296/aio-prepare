// CSES: Static Range Sum Queries
// prefix[i] = x_1 + ... + x_i, so sum(a..b) = prefix[b] - prefix[a-1] (telescoping).
// O(n + q).
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<ll> prefix(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        ll x;
        cin >> x;
        prefix[i] = prefix[i - 1] + x;
    }
    while (q--) {
        int a, b;
        cin >> a >> b;
        cout << prefix[b] - prefix[a - 1] << "\n";
    }
}
