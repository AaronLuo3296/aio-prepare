// CSES: Road Reparation
// Kruskal: take roads cheapest first, skipping any that would close a cycle (DSU).
// Correct by the cut property. If fewer than n - 1 roads were taken, the graph is
// disconnected. O(m log m).
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct DSU {
    vector<int> parent, size;
    DSU(int n) : parent(n + 1), size(n + 1, 1) { iota(parent.begin(), parent.end(), 0); }
    int find(int x) {                            // path compression
        while (parent[x] != x) x = parent[x] = parent[parent[x]];
        return x;
    }
    bool unite(int a, int b) {                   // union by size; false if already joined
        a = find(a), b = find(b);
        if (a == b) return false;
        if (size[a] < size[b]) swap(a, b);
        parent[b] = a;
        size[a] += size[b];
        return true;
    }
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<tuple<ll, int, int>> roads(m);
    for (auto& [c, a, b] : roads) cin >> a >> b >> c;
    sort(roads.begin(), roads.end());

    DSU dsu(n);
    ll total = 0;
    int taken = 0;
    for (auto [c, a, b] : roads)
        if (dsu.unite(a, b)) {
            total += c;
            taken++;
        }
    if (taken == n - 1) cout << total << "\n";
    else cout << "IMPOSSIBLE\n";
}
