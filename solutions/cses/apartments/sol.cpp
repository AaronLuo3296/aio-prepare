// CSES: Apartments
// Sort both lists. Walk them together: the smallest unmatched applicant either takes the
// smallest fitting apartment or (if none fits) is skipped. Exchange argument. O(n log n).
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> a(n), b(m);
    for (auto& x : a) cin >> x;
    for (auto& x : b) cin >> x;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    int i = 0, j = 0, matched = 0;
    while (i < n && j < m) {
        if (abs(a[i] - b[j]) <= k) {
            matched++, i++, j++;
        } else if (b[j] < a[i] - k) {
            j++;                     // apartment too small for everyone left
        } else {
            i++;                     // applicant wants something smaller than any left
        }
    }
    cout << matched << "\n";
}
