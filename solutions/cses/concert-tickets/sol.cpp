// CSES: Concert Tickets
// multiset keeps the remaining prices sorted with O(log n) erase.
// upper_bound(t) is the first price > t, so the element before it is the answer.
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    multiset<int> prices;
    for (int i = 0; i < n; i++) {
        int h;
        cin >> h;
        prices.insert(h);
    }
    for (int i = 0; i < m; i++) {
        int t;
        cin >> t;
        auto it = prices.upper_bound(t);
        if (it == prices.begin()) {
            cout << -1 << "\n";
        } else {
            --it;
            cout << *it << "\n";
            prices.erase(it);            // erase ONE copy (erase(value) would remove all)
        }
    }
}
