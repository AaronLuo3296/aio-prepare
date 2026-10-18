# Day 19: Directed acyclic graphs

**Goal:** topological sort (Kahn's algorithm and DFS), then DP over a DAG: longest path,
counting paths.
**Math bridge:** every finite partial order has a linear extension. A topological order is
exactly that, and a DP needs exactly such an order.

---

## 1. Kahn's algorithm

A DAG always has a vertex with in-degree 0 (extremal principle: walk backwards along
edges; without a cycle the walk must stop). Output it, delete it, repeat.

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n = 5;
    vector<pair<int, int>> edges = {{1, 2}, {3, 1}, {4, 5}};   // a must come before b
    vector<vector<int>> adj(n + 1);
    vector<int> indeg(n + 1, 0);
    for (auto [a, b] : edges) {
        adj[a].push_back(b);
        indeg[b]++;
    }
    queue<int> q;
    for (int v = 1; v <= n; v++)
        if (indeg[v] == 0) q.push(v);
    vector<int> order;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        order.push_back(u);
        for (int v : adj[u])
            if (--indeg[v] == 0) q.push(v);
    }
    if ((int)order.size() < n) cout << "cycle!\n";
    else for (int v : order) cout << v << " ";   // 3 4 1 5 2
    cout << "\n";
}
```

If fewer than N vertices come out, the rest contain a cycle (CSES *Course Schedule*:
print IMPOSSIBLE).

DFS alternative: the reverse of DFS **finishing** order is a topological order (CPH ch. 16.1).

## 2. DP on a DAG

Process vertices in topological order. When you reach u, every edge into u has already
been processed, so `dp[u]` is final.

- **Longest path** (AtCoder DP *G*): `len[v] = max(len[v], len[u] + 1)` over edges u → v.
- **Count paths 1 → n** (CSES *Game Routes*): `ways[v] += ways[u]`, with `ways[1] = 1`, mod 10⁹+7.
- **Longest route 1 → n, printed** (CSES *Longest Flight Route*): as longest path, but
  start only from vertex 1 (unreachable = 0) and store `parent[v]` to rebuild the route.

## 3. Every DP is a DAG

The states of any DP are vertices, and "state A is used to compute state B" is an edge
A → B. The DP is correct only if this graph has no cycle, and your loop order must be a
topological order of it. Look back: in Coin Combinations (Day 12) the edges go from
smaller sums to larger sums, so "increasing s" is a topological order. This view explains
why some DPs need a careful loop order (knapsack downwards, Day 13).

## 4. Practice

1. CSES *Course Schedule*, *Longest Flight Route*, *Game Routes*.
2. AtCoder DP *G: Longest Path*.
3. Read CPH ch. 16, UG [Topological Sort](https://usaco.guide/gold/toposort) and
   CPA [Topological sort](https://cp-algorithms.com/graph/topological-sort.html).

Reference solutions: `solutions/cses/` (`course-schedule`, `longest-flight-route`,
`game-routes`) and `solutions/atcoder-dp/longest-path`.

**Checkpoint:** explain why *every* DP is a DAG of states, using Coin Combinations II as
the example.
