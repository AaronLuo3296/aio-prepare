// CSES: Book Shop
// 0/1 knapsack. best[w] = max pages with total price <= w using the books so far.
// Loop w DOWNWARDS so best[w - price] still describes the previous books (each book once).
// O(n x) time, O(x) memory.
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, x;
    cin >> n >> x;
    vector<int> price(n), pages(n);
    for (auto& v : price) cin >> v;
    for (auto& v : pages) cin >> v;
    vector<int> best(x + 1, 0);
    for (int i = 0; i < n; i++)
        for (int w = x; w >= price[i]; w--)
            best[w] = max(best[w], best[w - price[i]] + pages[i]);
    cout << best[x] << "\n";
}
