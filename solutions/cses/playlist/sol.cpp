// CSES: Playlist
// Two pointers: for each right end r, l is the smallest start with no repeat in [l, r].
// l never moves left, so the total work is O(n log n) with a map of last positions.
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    map<int, int> last;                  // song -> last index seen
    int l = 0, best = 0;
    for (int r = 0; r < n; r++) {
        int k;
        cin >> k;
        auto it = last.find(k);
        if (it != last.end()) l = max(l, it->second + 1);
        last[k] = r;
        best = max(best, r - l + 1);
    }
    cout << best << "\n";
}
