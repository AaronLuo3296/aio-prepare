# Day 17: Weighted shortest paths

**Goal:** Dijkstra with a priority queue, Bellman–Ford and Floyd–Warshall, and knowing
which one to use.
**Math bridge:** Dijkstra is an extremal argument. Among vertices not yet finalised, the
one with the smallest tentative distance cannot be improved, because every other route to
it leaves the finalised set through a vertex that is already at least as far.

---

## 1. Which algorithm?

| Situation | Algorithm | Cost |
|-----------|-----------|------|
| unweighted (all edges 1) | BFS (Day 15) | O(N + M) |
| weights ≥ 0, one source | Dijkstra | O((N + M) log M) |
| negative weights, one source | Bellman–Ford | O(N·M) |
| all pairs, N ≤ 500 | Floyd–Warshall | O(N³) |

## 2. Dijkstra

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n = 3;
    vector<vector<pair<int, ll>>> adj(n + 1);      // (neighbour, weight)
    adj[1] = {{2, 6}, {3, 2}};
    adj[3] = {{2, 3}};

    vector<ll> dist(n + 1, LLONG_MAX);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;   // min-heap
    dist[1] = 0;
    pq.push({0, 1});
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u]) continue;                 // stale entry: u was already improved
        for (auto [v, w] : adj[u])
            if (d + w < dist[v]) {
                dist[v] = d + w;
                pq.push({dist[v], v});
            }
    }
    for (int v = 1; v <= n; v++) cout << dist[v] << " ";   // 0 5 2
    cout << "\n";
}
```

Three bugs to avoid:
1. `priority_queue` is a **max**-heap by default. Use `greater<>` (or push negated distances).
2. Forgetting the stale-entry check makes it O(M²) in bad cases.
3. Path lengths reach 10⁵ · 10⁹: use `long long`.

## 3. Floyd–Warshall

`d[i][j]` starts as the edge weight (∞ if none, 0 on the diagonal). Then

```
for k: for i: for j: d[i][j] = min(d[i][j], d[i][k] + d[k][j])
```

Invariant: after round k, `d[i][j]` is the shortest path using only intermediate
vertices 1..k. That is induction on k, and it is why **k must be the outer loop**. Use
∞ = `LLONG_MAX / 4` so that ∞ + ∞ does not overflow. Keep the cheapest of parallel edges.
Solution: `solutions/cses/shortest-routes-ii`.

## 4. Bellman–Ford

Relax every edge N − 1 times. A shortest path has at most N − 1 edges, and after round i
every shortest path with ≤ i edges is correct (induction). If an N-th round still improves
something, there is a negative cycle. Read CPH ch. 13.1.

## 5. State-expanded graphs (CSES *Flight Discount*)

"You may halve the price of **one** flight." Make two copies of every city: (v, 0) = coupon
unused, (v, 1) = coupon used. A flight u → v with price w gives edges
(u,0)→(v,0) cost w, (u,1)→(v,1) cost w, and (u,0)→(v,1) cost ⌊w/2⌋. Then run Dijkstra
on the 2N states. This "add the extra information to the state" trick is the same idea as
adding a dimension to a DP.

## 6. Practice

1. CSES *Shortest Routes I*, *Shortest Routes II*, *Flight Discount*.
2. Read CPH ch. 13, UG [Shortest Paths](https://usaco.guide/gold/shortest-paths) and
   CPA [Dijkstra](https://cp-algorithms.com/graph/dijkstra.html).
   Watch 6.006 Lectures 11–13.

Reference solutions: `solutions/cses/` (`shortest-routes-i`, `shortest-routes-ii`,
`flight-discount`).

**Checkpoint:** by hand, find a 3-vertex graph with one negative edge where Dijkstra gives
the wrong answer, and point to the step of the proof that breaks.
