// CSES: Restaurant Customers
// Sweep line: +1 at each arrival, -1 at each departure, process events in time order
// and track the running maximum. All times are distinct, so ties never occur. O(n log n).
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<pair<int, int>> events;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        events.push_back({a, +1});
        events.push_back({b, -1});
    }
    sort(events.begin(), events.end());

    int inside = 0, best = 0;
    for (auto [time, delta] : events) {
        inside += delta;
        best = max(best, inside);
    }
    cout << best << "\n";
}
