// CSES: Distinct Numbers
// Sort, then equal values are adjacent; unique() keeps one of each. O(n log n).
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    sort(a.begin(), a.end());
    cout << unique(a.begin(), a.end()) - a.begin() << "\n";
}
