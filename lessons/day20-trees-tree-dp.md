# Day 20: Trees and tree DP

**Goal:** root a tree, compute subtree quantities bottom-up, find the diameter, and do DP
on trees.
**Math bridge:** a tree has N − 1 edges and a unique path between any two vertices, and
it always has a leaf (extremal principle). The diameter comes from "the farthest vertex
from the farthest vertex".

---

## 1. Rooting a tree without recursion

Pick a root (vertex 1). A BFS from it lists every parent before its children. Walking
that list **backwards** visits children before parents, which is exactly the order a
bottom-up DP needs. No recursion, so no stack overflow on a 2·10⁵-vertex path.

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n = 5;
    vector<vector<int>> adj(n + 1);
    for (auto [a, b] : vector<pair<int, int>>{{1, 2}, {1, 3}, {3, 4}, {3, 5}}) {
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<int> order = {1}, parent(n + 1, 0);
    for (size_t i = 0; i < order.size(); i++)
        for (int v : adj[order[i]])
            if (v != parent[order[i]]) {
                parent[v] = order[i];
                order.push_back(v);
            }

    vector<int> size(n + 1, 1);                     // subtree sizes, bottom-up
    for (int i = n - 1; i > 0; i--) size[parent[order[i]]] += size[order[i]];
    for (int v = 1; v <= n; v++) cout << size[v] << " ";   // 5 1 3 1 1
    cout << "\n";
}
```

(`parent[1] = 0` is safe here because there is no vertex 0.) CSES *Subordinates* is this
loop, with the answer size[v] − 1.

The recursive version (`dfs(v, parent)`) is shorter and fine on most judges. Know both.

## 2. Diameter: double BFS

BFS from any vertex s; let a be the farthest vertex. BFS from a; the largest distance is the
diameter, reached at some b.

Why: let (x, y) be a diameter path. Using unique paths in a tree, one shows that the
farthest vertex from s can be taken as an end of a diameter (case analysis on where the
s–a path meets the x–y path). Writing this up properly is today's checkpoint.

CSES *Tree Distances I* ("farthest vertex from each v"): the farthest vertex from any v is
a or b, so the answer is max(dist(a, v), dist(b, v)): three BFS runs.

## 3. Tree DP

State: something about the subtree of v, often with a flag for v itself.

- **Independent sets** (AtCoder DP *P*): `white[v]` / `black[v]` = number of valid
  colourings of v's subtree with v white / black. Then
  white[v] = Π over children c of (white[c] + black[c]) and black[v] = Π white[c].
- **Maximum matching** (CSES *Tree Matching*): a DP with "v matched / unmatched", or the
  greedy "match a leaf with its parent, delete both, repeat". Proving the greedy is an
  exchange argument: some maximum matching uses that leaf's edge.

**Rerooting** (preview): when you need the answer *for every root*, compute the subtree DP
once and then push information down from parent to child. CSES *Tree Distances II* is
the classic exercise.

## 4. Practice

1. CSES *Subordinates*, *Tree Diameter*, *Tree Distances I*, *Tree Matching*.
2. AtCoder DP *P: Independent Set*.
3. Read CPH ch. 14.

Reference solutions: `solutions/cses/` (`subordinates`, `tree-diameter`,
`tree-distances-i`, `tree-matching`) and `solutions/atcoder-dp/independent-set`.

**Checkpoint:** prove the double-BFS diameter algorithm is correct.
