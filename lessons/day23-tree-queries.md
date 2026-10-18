# Day 23: Tree queries (binary lifting, LCA, Euler tour)

**Goal:** jump k levels up a tree in O(log k), find lowest common ancestors, compute tree
distances, and turn subtrees into array ranges.
**Math bridge:** every integer is a sum of distinct powers of 2. Binary lifting is fast
exponentiation applied to the "parent" function: if up_j = parent^(2ʲ), then
up_j = up_{j−1} ∘ up_{j−1}, and parent^k is a composition of the up_j for the set bits of k.

---

## 1. Binary lifting

`up[v][j]` = the 2ʲ-th ancestor of v. Build level j from level j − 1 for all vertices, then
answer "k-th ancestor" one bit at a time.

```cpp
#include <bits/stdc++.h>
using namespace std;
const int LOG = 18;                   // 2^18 > 2e5, the usual CSES bound

int main() {
    int n = 6;
    vector<int> boss = {0, 0, 1, 2, 3, 4, 5};      // boss[v]; 0 = none (a path 1-2-...-6)
    vector<array<int, LOG>> up(n + 1);
    for (int v = 0; v <= n; v++) up[v][0] = boss[v];
    for (int j = 1; j < LOG; j++)
        for (int v = 0; v <= n; v++) up[v][j] = up[up[v][j - 1]][j - 1];

    auto kth = [&](int v, int k) {
        for (int j = 0; j < LOG && v != 0; j++)
            if (k >> j & 1) v = up[v][j];
        return v == 0 ? -1 : v;
    };
    cout << kth(6, 3) << " " << kth(6, 5) << " " << kth(6, 6) << "\n";   // 3 1 -1
}
```

Vertex 0 acts as a **sentinel**: it is the boss of the root and of itself, so a jump past
the root sticks at 0 instead of indexing out of bounds. CSES *Company Queries I* is
exactly this program.

## 2. Lowest common ancestor

1. Lift the deeper vertex until both have the same depth (k = the depth difference).
2. If they are now equal, that vertex is the LCA.
3. Otherwise, for j from high to low: if up[a][j] ≠ up[b][j], jump both. They stay
   *below* the LCA the whole time, and end as its two children. Answer: up[a][0].

Step 3 is a binary search on the depth of the LCA. The predicate "the 2ʲ-th ancestors
differ" is monotone in the jump length: once two ancestors agree, every higher ancestor
agrees too.

Depths come from a BFS from the root (parents before children). Do not assume
`boss[i] < i` unless the statement promises it.

## 3. Distances

The unique path a–b climbs from a to lca(a, b) and descends to b, so

dist(a, b) = depth[a] + depth[b] − 2·depth[lca(a, b)].

Weighted trees: replace depth by distance from the root. CSES *Distance Queries*.

## 4. Euler tour: subtrees become ranges

Number the vertices in DFS order (`tin[v]`). The subtree of v is visited in one
contiguous stretch, so it occupies positions [tin[v], tin[v] + size[v] − 1]. A subtree
query is now a range query, and Day 22's Fenwick tree finishes the job. CSES *Subtree
Queries*: point update = Fenwick `add`, subtree sum = Fenwick `range`.

Use an iterative DFS (an explicit stack): a path of 2·10⁵ vertices can overflow the call
stack. Pushing all children at once still gives a valid DFS order, because each child's
whole subtree is popped before its siblings.

## 5. Practice

1. CSES *Company Queries I*, *Company Queries II*, *Distance Queries*, *Subtree Queries*.
2. Read CPH ch. 18.

Reference solutions: `solutions/cses/` (`company-queries-i`, `company-queries-ii`,
`distance-queries`, `subtree-queries`).

**Checkpoint:** prove dist(u, v) = depth(u) + depth(v) − 2·depth(lca(u, v)), and use it to
pass *Distance Queries*.
