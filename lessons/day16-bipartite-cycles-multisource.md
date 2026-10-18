# Day 16: Bipartiteness, cycles and multi-source BFS

**Goal:** 2-colour a graph, find and **print** a cycle, and run BFS from many sources at once.
**Math bridge:** a graph is bipartite ⇔ it has no odd cycle. You know the proof. In code,
the BFS layers *are* the proof: colour by layer parity, and any conflict exhibits an odd
cycle.

---

## 1. Two-colouring (CSES *Building Teams*)

Give the start vertex colour 1, each newly discovered neighbour the opposite colour.
If an edge ever joins two vertices of the same colour, the graph is not bipartite.
Run it from every uncoloured vertex: the graph may be disconnected.

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n = 4;
    vector<vector<int>> adj(n + 1);
    for (auto [a, b] : vector<pair<int, int>>{{1, 2}, {2, 3}, {3, 4}, {4, 1}}) {
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<int> color(n + 1, 0);
    bool ok = true;
    for (int s = 1; s <= n; s++) {
        if (color[s]) continue;
        color[s] = 1;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : adj[u]) {
                if (!color[v]) {
                    color[v] = 3 - color[u];        // 1 <-> 2
                    q.push(v);
                } else if (color[v] == color[u]) {
                    ok = false;
                }
            }
        }
    }
    cout << (ok ? "bipartite" : "odd cycle") << "\n";   // a 4-cycle is bipartite
}
```

## 2. Finding a cycle (CSES *Round Trip*)

In an **undirected** DFS, every non-tree edge goes from a vertex u to an *ancestor* v still
on the current path. Such an edge (other than the one back to u's parent) closes a cycle
v → … → u → v of length ≥ 3. Keep `parent[]` and a "currently on the path" mark; when the
cycle is found, walk `parent` from u back to v to print it.

The checkpoint for today is to output the actual cycle, not just "yes". Printing the
witness is a separate skill and judges often require it. See
`solutions/cses/round-trip`, which also shows an iterative DFS with an explicit stack.

For **directed** graphs the condition is the same: an edge to a vertex on the current path.
You will need that on Day 19.

## 3. Multi-source BFS (CSES *Monsters*)

To get, for every cell, the distance to the **nearest** of many sources, push all sources
into the queue with distance 0 before starting. This is one BFS on a graph with an extra
"super-source" joined to every real source by an edge of length 0. Cost is still O(N + M).

*Monsters* then needs a second BFS for yourself: enter a cell only if you arrive
**strictly before** every monster (`mine + 1 < monster`). If you reach any border cell,
you escape. Why is it enough to compare with the monsters' shortest distances? A monster
that can reach a cell at time t can also wait there (or walk back and forth), so it can be
there at every later time.

## 4. Practice

1. CSES *Building Teams*, *Round Trip*, *Monsters*.
2. Re-read UG [Graph Traversal](https://usaco.guide/silver/graph-traversal) (the
   bipartite and cycle sections) and CPH ch. 12.

Reference solutions: `solutions/cses/` (`building-teams`, `round-trip`, `monsters`).
These problems accept many correct answers, so their tests use a `check.py`.

**Checkpoint:** *Round Trip* outputs an actual cycle, and you can explain why every
non-tree edge in an undirected DFS goes to an ancestor.
