# Day 28: Consolidation

**Goal:** turn four weeks of material into skills you can use from a blank file, and build
your own template library.
**Math bridge:** you only know a proof once you can reproduce it without the book. The
same holds for an algorithm and an empty editor.

---

## 1. Re-solve from a blank file (about 2.5 hours)

Choose **five** problems from your error log that you got wrong or needed a hint for.
Take at least one from each of: graphs, DP, range queries. For each:

1. Close all previous code. Re-read only the statement.
2. Write the one-paragraph proof and complexity (as on every day), then code it.
3. Submit. If it fails, debug without looking at the old solution for at least 15 minutes.

## 2. Your personal template (about 1.5 hours)

Write these from memory into one file, then compare with the reference solutions named in
brackets. Every piece should be short enough to retype in a contest.

| Piece | Reference |
|-------|-----------|
| fast I/O + `long long` main skeleton | `templates/template.cpp` |
| BFS on a grid | `solutions/cses/labyrinth` |
| Dijkstra | `solutions/cses/shortest-routes-i` |
| DSU (path compression + union by size) | `solutions/cses/road-construction` |
| Fenwick tree / bottom-up segment tree | `solutions/cses/dynamic-range-sum-queries`, `dynamic-range-minimum-queries` |
| `power` + factorial tables | `solutions/cses/binomial-coefficients` |
| binary search on the answer | `solutions/cses/factory-machines` |

A compact starting point that compiles:

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD = 1e9 + 7;

struct DSU {
    vector<int> p, sz;
    DSU(int n) : p(n), sz(n, 1) { iota(p.begin(), p.end(), 0); }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    bool unite(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        p[b] = a;
        sz[a] += sz[b];
        return true;
    }
};

ll power(ll a, ll b) {
    ll r = 1;
    for (a %= MOD; b > 0; b >>= 1, a = a * a % MOD)
        if (b & 1) r = r * a % MOD;
    return r;
}

vector<ll> dijkstra(const vector<vector<pair<int, ll>>>& adj, int src) {
    vector<ll> dist(adj.size(), LLONG_MAX);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
    pq.push({dist[src] = 0, src});
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u]) continue;                    // stale entry
        for (auto [v, w] : adj[u])
            if (d + w < dist[v]) pq.push({dist[v] = d + w, v});
    }
    return dist;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    DSU d(4);
    d.unite(0, 1);
    vector<vector<pair<int, ll>>> adj = {{{1, 5}, {2, 1}}, {}, {{1, 2}}};
    cout << d.find(1) << " " << power(2, 30) << " " << dijkstra(adj, 0)[1] << "\n";  // 0 73741817 3
}
```

## 3. Targeted reading (remaining time)

Count your error-log tags. For your two most frequent **idea** categories, re-read the
CPH chapters behind them (chapter list in the plan). For **implementation** errors,
redo Day 7's stress-testing drill on one of today's five problems.

**Checkpoint:** five problems re-solved from blank files, and a personal template file
that compiles and that you can explain line by line.
