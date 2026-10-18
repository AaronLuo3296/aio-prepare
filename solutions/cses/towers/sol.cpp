// CSES: Towers
// Greedy: put each cube on the tower whose top is the smallest value strictly greater than
// the cube; open a new tower if none exists. Exchange argument: any optimal solution can be
// changed to make this choice without using more towers. Multiset of tops: O(n log n).
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    multiset<int> tops;
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        auto it = tops.upper_bound(k);      // first top > k
        if (it != tops.end()) tops.erase(it);
        tops.insert(k);
    }
    cout << tops.size() << "\n";
}
