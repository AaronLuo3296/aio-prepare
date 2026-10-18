// CSES: Movie Festival
// Greedy: always watch the movie that ends first among those still possible.
// Exchange argument: swapping any optimal schedule's first movie for the earliest-ending
// one keeps it valid. O(n log n).
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<pair<int, int>> movies(n);    // (end, start) so sort orders by end
    for (auto& [b, a] : movies) cin >> a >> b;
    sort(movies.begin(), movies.end());

    int watched = 0, freeAt = 0;
    for (auto [b, a] : movies) {
        if (a >= freeAt) {
            watched++;
            freeAt = b;
        }
    }
    cout << watched << "\n";
}
