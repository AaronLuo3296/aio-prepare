# Phase A.3: Negative weights and functional graphs

*Months 2–3, [roadmap](../plan/after-30-days.md#phase-a-months-23-finish-the-core). About
one week, alongside the rest of the CSES *Graph Algorithms* section.*

**Goal:** shortest paths when edges may be negative (Bellman–Ford), finding a negative
cycle, and answering "where am I after k steps?" in a graph where every node has exactly
one outgoing edge.
**Math bridge:** Bellman–Ford's correctness is induction on the number of edges. After
round i, d[v] is at most the length of the best walk to v with at most i edges. A
functional graph is the graph of a function f: [n] → [n]. Iterating f is composition, and
binary lifting is fast exponentiation (Day 24) applied to functions instead of numbers.

**Read:** CPH ch. 13.1 (Bellman–Ford), ch. 16.3–16.4 (successor graphs, cycle detection) ·
CPA [Bellman–Ford](https://cp-algorithms.com/graph/bellman_ford.html), [negative
cycle](https://cp-algorithms.com/graph/finding-negative-cycle-in-graph.html).

---

## 1. Bellman–Ford

Relax every edge, n − 1 times. A shortest path uses at most n − 1 edges, so if there is no
negative cycle the distances are final after n − 1 rounds. If round n still improves
something, a negative cycle exists. O(nm), fine for n = 2500 and m = 5000.

```cpp
for (int round = 0; round < n - 1; round++)
    for (auto [a, b, w] : edges)
        if (d[a] != INF && d[a] + w < d[b]) d[b] = d[a] + w;
```

The `d[a] != INF` guard matters. Without it, INF + (negative) looks like a real distance.

Why not Dijkstra? Dijkstra finalises the closest unfinished node, assuming no later edge
can make it shorter. A negative edge breaks that assumption.

## 2. Longest path = shortest path with negated weights

*High Score* asks for the **maximum** score from 1 to n. Negate the weights (or flip every
comparison) and it becomes a shortest-path problem. The answer is unbounded (−1) only if a
positive cycle lies on some route from 1 to n. A positive cycle that cannot reach n does
not count. The standard fix:

1. Run n − 1 rounds.
2. Run n more rounds. Mark every node that still improves, and every node reached from a
   marked node.
3. Answer −1 iff a marked node can reach n. Compute that with one DFS from n in the
   **reversed** graph.

The test files include a positive cycle that is reachable from 1 but cannot reach n. That
case breaks the naive "did anything improve in round n?" check.

## 3. Finding a negative cycle

*Cycle Finding*: start every d at 0 (a virtual source with 0-weight edges to all nodes,
so cycles anywhere are found), and record par[v] whenever d[v] improves. If round n
relaxes an edge into x, then x is on a negative cycle or reachable from one. Walking par
n times from x is guaranteed to land **on** the cycle. Then follow par until you return to
that node, and reverse the list to get edges in forward order.

## 4. Functional graphs (successor graphs)

Every node has exactly one out-edge, t[v]. Each weakly connected component is one cycle
with trees hanging into it ("rho" shape: a tail, then a loop).

*Planets Queries I*: the planet after k ≤ 10⁹ teleports. Precompute
up[j][v] = t applied 2ʲ times, by up[j][v] = up[j−1][up[j−1][v]]. A query takes the jumps
for the set bits of k. This is O(log k), the same structure as Day 23's binary lifting for
ancestors, and Day 24's fast exponentiation.

Also learn **Floyd's cycle finding** (tortoise and hare, CPH 16.4). It finds the cycle in
the rho with O(1) memory, and *Planets Cycles* (cycle length reachable from each node) is a
good exercise for it.

## 5. Practice

1. CSES *High Score*, *Cycle Finding*, *Planets Queries I* (reference solutions below).
2. CSES *Graph Algorithms*: *Flight Routes* (k shortest routes: Dijkstra, popping each
   node up to k times), *Round Trip II* (directed cycle), *Investigation* (Dijkstra plus
   counting and min/max edge count), *Planets Queries II*, *Planets Cycles*.
3. Rewrite Bellman–Ford from memory in under 5 minutes. It is short enough to be a
   reflex, and IOI subtasks with small n often accept it where Dijkstra does not apply.

Reference solutions: `solutions/cses/` (`high-score`, `cycle-finding`, `planets-queries-i`).
*Cycle Finding* has many valid outputs, so it has a `check.py`.

**Checkpoint:** explain why n − 1 rounds suffice and what round n detects, and get *High
Score* accepted. The −1 case is where most first attempts fail.
