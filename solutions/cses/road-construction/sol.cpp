// CSES: Road Construction
// DSU tracks components as roads are added. The number of components drops by one on
// each successful union; the largest size only ever grows. O(m alpha(n)).
#include <bits/stdc++.h>
using namespace std;
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
    DSU dsu(n);
    int components = n, largest = 1;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        if (dsu.unite(a, b)) {
            components--;
            largest = max(largest, dsu.size[dsu.find(a)]);
        }
        cout << components << " " << largest << "\n";
    }
}
