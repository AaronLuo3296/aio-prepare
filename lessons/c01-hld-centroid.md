# Phase C.1: Heavy-light and centroid decomposition

*Months 7–12, [roadmap](../plan/after-30-days.md#phase-c-months-712-ioi-toolkit-part-2-and-full-past-papers).
About three weeks: these two are the backbone of hard IOI tree tasks.*

**Goal:** answer path queries with updates on a tree (heavy-light decomposition, HLD),
and count or optimise over **all** paths of a tree (centroid decomposition).
**Math bridge:** both rest on halving. In HLD, a light edge leads into a subtree at most
half the size of its parent's, so a root-to-node path crosses at most log₂ n light edges.
A centroid splits a tree into pieces of size ≤ n/2, so recursing on the pieces has depth
at most log₂ n. That is the same argument as "each element changes set O(log n) times"
in small-to-large merging.

**Read:** CPH ch. 18 · UG [HLD](https://usaco.guide/plat/hld),
[Centroid](https://usaco.guide/plat/centroid) · CPA
[HLD](https://cp-algorithms.com/graph/hld.html).

---

## 1. Heavy-light decomposition

For each node, its **heavy child** is the child with the largest subtree. The other
edges are light. Heavy edges form vertical **chains**. Give the nodes positions so that
every chain is a contiguous interval, by assigning positions down each chain starting
from its head. Then:

- A path a–b splits into O(log n) chain pieces: repeatedly lift whichever endpoint has
  the **deeper chain head**, querying the interval [pos[head], pos[node]], until both are
  on the same chain. Finish with the interval between them.
- Each piece is a segment-tree query, so a path query costs O(log² n). Point updates are
  ordinary segment-tree updates at pos[v].
- Subtree queries can work too: if positions come from a DFS that visits the heavy child
  first, every subtree is also contiguous, [pos[v], pos[v] + sz[v] − 1]. The reference
  solution's BFS-based layout does **not** have this property. Use the DFS layout when a
  task mixes path and subtree queries.

*Path Queries II* (max on a path, point updates) is the canonical problem. The reference
solution builds everything **iteratively** (BFS order for sizes, then a loop that starts a
chain at every node that is not a heavy child), because CSES includes path-shaped trees
of 2·10⁵ nodes. It is about 70 lines: practise typing it.

Values on **edges** instead of nodes: store each edge's value at its lower endpoint, and
skip the LCA's own position in the last interval.

## 2. Centroid decomposition

A **centroid** is a node whose removal leaves pieces of size ≤ n/2. Find it by walking
from any node towards the side with more than n/2 nodes (*Finding a Centroid*).

To process all paths: every path either passes through the centroid c, or lies entirely
inside one piece. So

1. count/optimise the paths through c, by combining depth information from c's subtrees
   one at a time;
2. delete c and recurse into each piece.

Each node appears in O(log n) levels, so if step 1 is linear in the piece size, the total
is O(n log n).

*Fixed-Length Paths I* (count paths with exactly k edges): for c, keep cnt[d] = number of
nodes at depth d in the subtrees processed so far (cnt[0] = 1 for c). For each new
subtree, first add cnt[k − d] for each of its nodes at depth d, **then** insert its depths.
Inserting first would count paths that go down and back up the same subtree. Reset only
the cnt entries you used. Clearing the whole array costs O(n) per centroid, O(n²) in total.

Use centroid decomposition when the question is about **all pairs or all paths**: count
paths with a property, the closest marked node to v (Codeforces *Xenia and Tree*), or
the minimum cost path of length exactly k (IOI 2011 *Race*).

## 3. Which one?

| Question shape | Tool |
|----------------|------|
| One given path, many queries, updates | HLD + segment tree |
| Subtree query / update | Euler tour (Day 23) |
| Aggregate over all paths | centroid decomposition |
| Path query, no updates, invertible operation | prefix sums from the root + LCA (Day 23) |

## 4. Practice

1. CSES *Finding a Centroid*, *Path Queries II*, *Fixed-Length Paths I* (reference
   solutions below).
2. CSES *Path Queries* (root-path sums: Euler tour + Fenwick), *Distinct Colors*
   (small-to-large merging), *Fixed-Length Paths II* (lengths in [k₁, k₂]: centroid
   decomposition plus prefix sums of cnt).
3. IOI 2011 *Race* on [oj.uz](https://oj.uz/problems/source/22). It is centroid
   decomposition with a min instead of a count.

Reference solutions: `solutions/cses/` (`finding-a-centroid`, `path-queries-ii`,
`fixed-length-paths-i`).

**Checkpoint:** HLD with a segment tree from memory in under 25 minutes, and IOI 2011
*Race* solved for full marks.
