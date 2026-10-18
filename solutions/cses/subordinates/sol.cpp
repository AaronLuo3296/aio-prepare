// CSES: Subordinates
// Subordinates of v = sum over children c of (1 + subordinates of c). Compute children
// before parents by walking a BFS order backwards. O(n).
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<vector<int>> children(n + 1);
    vector<int> boss(n + 1, 0);
    for (int i = 2; i <= n; i++) {
        cin >> boss[i];
        children[boss[i]].push_back(i);
    }
    vector<int> order = {1};
    for (size_t i = 0; i < order.size(); i++)
        for (int c : children[order[i]]) order.push_back(c);

    vector<int> sub(n + 1, 0);
    for (int i = n - 1; i > 0; i--) {
        int v = order[i];
        sub[boss[v]] += 1 + sub[v];
    }
    for (int v = 1; v <= n; v++) cout << sub[v] << " ";
    cout << "\n";
}
