// CSES: Increasing Subsequence
// d[len] = smallest possible last value of a strictly increasing subsequence of length
// len+1. d stays sorted, so each x replaces the first d[len] >= x (lower_bound), or extends
// d when x is larger than everything. The answer is d.size(). O(n log n).
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> d;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        auto it = lower_bound(d.begin(), d.end(), x);   // strict: equal values replace
        if (it == d.end()) d.push_back(x);
        else *it = x;
    }
    cout << d.size() << "\n";
}
