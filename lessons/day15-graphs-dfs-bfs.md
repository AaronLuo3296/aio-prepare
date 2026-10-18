# Day 15: Graph representation, DFS and BFS

**Goal:** store a graph as adjacency lists, traverse it with DFS and BFS, count connected
components, flood-fill a grid, and rebuild a shortest path.
**Math bridge:** your graph theory carries over unchanged. The handshake lemma
(Σ deg(v) = 2M) says adjacency lists hold 2M entries, so one traversal costs O(N + M).

---

## 1. Reading a graph

Input is almost always "N M, then M lines `a b`" with vertices numbered 1..N. Store, for
each vertex, the list of its neighbours:

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n = 4;
    vector<pair<int, int>> edges = {{1, 2}, {2, 3}, {1, 3}, {3, 4}};
    vector<vector<int>> adj(n + 1);                 // index 0 unused
    for (auto [a, b] : edges) {
        adj[a].push_back(b);
        adj[b].push_back(a);                        // undirected: store both directions
    }
    for (int v = 1; v <= n; v++) {
        cout << v << ":";
        for (int u : adj[v]) cout << " " << u;
        cout << "\n";
    }
}
```

An adjacency **matrix** (`bool g[N][N]`) costs N² memory: fine for N ≤ 2000, impossible
for N = 10⁵.

## 2. DFS: go deep, mark as you go

```cpp
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
vector<bool> seen;

void dfs(int u) {
    seen[u] = true;
    for (int v : adj[u])
        if (!seen[v]) dfs(v);
}

int main() {
    int n = 6;
    adj.assign(n + 1, {});
    seen.assign(n + 1, false);
    for (auto [a, b] : vector<pair<int, int>>{{1, 2}, {2, 3}, {4, 5}}) {
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    int components = 0;
    for (int v = 1; v <= n; v++)
        if (!seen[v]) {
            components++;
            dfs(v);
        }
    cout << components << "\n";                     // 3: {1,2,3} {4,5} {6}
}
```

Recursion depth can reach N. Most judges allow that, but if you get a mysterious crash on
a long path graph, switch to an explicit stack (see `solutions/cses/building-roads`).

## 3. BFS: layer by layer

BFS visits vertices in order of distance from the source, using a queue.

**Claim.** When BFS from s finishes, dist[v] is the length of a shortest s–v path.
**Proof sketch.** Induction on d: the queue holds all of layer d before any vertex of
layer d+1, and a vertex at distance d+1 is first discovered from some vertex at distance d.

To **rebuild the path**, store `parent[v]` (the vertex that discovered v) and walk back
from the target, then reverse. Solution: `solutions/cses/message-route`.

## 4. Grids are graphs

A cell (r, c) is a vertex and its 4 neighbours are (r±1, c) and (r, c±1). Loop over
direction arrays instead of writing four `if`s:

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<string> g = {"..#", ".##", "..."};
    int n = g.size(), m = g[0].size();
    const int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};
    vector<vector<int>> dist(n, vector<int>(m, -1));
    queue<pair<int, int>> q;
    q.push({0, 0});
    dist[0][0] = 0;
    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;     // off the grid
            if (g[nr][nc] == '#' || dist[nr][nc] != -1) continue;    // wall or seen
            dist[nr][nc] = dist[r][c] + 1;
            q.push({nr, nc});
        }
    }
    cout << dist[2][2] << "\n";                     // 4
}
```

*Counting Rooms* is "count components" on this graph (flood fill). *Labyrinth* is BFS
plus path rebuilding: store the **direction** used to enter each cell, then walk back from B.

## 5. Practice

1. CSES *Counting Rooms*, *Building Roads*, *Message Route*, *Labyrinth*.
2. Read CPH ch. 11–12, UG [Intro to Graphs](https://usaco.guide/bronze/intro-graphs),
   [Graph Traversal](https://usaco.guide/silver/graph-traversal) and
   [Flood Fill](https://usaco.guide/silver/flood-fill). Reference:
   CPA [BFS](https://cp-algorithms.com/graph/breadth-first-search.html),
   [DFS](https://cp-algorithms.com/graph/depth-first-search.html).
3. Watch 6.006 Lectures 9–10; play with [VisuAlgo](https://visualgo.net/en) graph traversal.

Reference solutions: `solutions/cses/` (`counting-rooms`, `building-roads`,
`message-route`, `labyrinth`).

**Checkpoint:** write out the proof that BFS gives shortest paths in unweighted graphs
(induction on distance layers).
