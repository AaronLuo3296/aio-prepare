// CSES: Ferris Wheel
// Sort. The heaviest child rides with the lightest if they fit, else alone.
// Exchange argument: any optimal pairing can be rearranged to do this. O(n log n).
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, x;
    cin >> n >> x;
    vector<int> p(n);
    for (auto& w : p) cin >> w;
    sort(p.begin(), p.end());

    int i = 0, j = n - 1, gondolas = 0;
    while (i <= j) {
        if (i < j && p[i] + p[j] <= x) i++;
        j--;
        gondolas++;
    }
    cout << gondolas << "\n";
}
