# Phase C.2: Flows, cuts and matchings

*Months 7–12, [roadmap](../plan/after-30-days.md#phase-c-months-712-ioi-toolkit-part-2-and-full-past-papers).
About two weeks.*

**Goal:** compute maximum flows, read a minimum cut off the residual graph, find maximum
bipartite matchings, and recognise problems that are secretly one of these.
**Math bridge:** max-flow min-cut is LP duality made combinatorial, and its proof is an
extremal argument: when no augmenting path exists, the nodes reachable from the source
form a cut whose capacity equals the flow. König's theorem (in a bipartite graph, maximum
matching = minimum vertex cover) and Hall's marriage theorem follow from it. You may know
those from olympiad combinatorics. Here they become algorithms.

**Read:** CPH ch. 20 · CPA [Dinic](https://cp-algorithms.com/graph/dinic.html),
[Kuhn's matching](https://cp-algorithms.com/graph/kuhn_maximum_bipartite_matching.html).

---

## 1. Residual graphs and augmenting paths

Every edge u → v with capacity c gets a reverse edge v → u with capacity 0. Pushing f
units along u → v lowers its capacity by f and raises the reverse edge by f, so a later
path can "undo" the flow. An **augmenting path** is any source–sink path of positive
residual capacity. Push along it, repeat, stop when none exists.

Store edges in one array so that edge `i ^ 1` is the reverse of edge `i`. That makes the
update two lines. See the `Dinic` struct in `solutions/cses/download-speed/sol.cpp`.

## 2. Dinic's algorithm

Ford–Fulkerson with arbitrary paths can be slow. Dinic:

1. BFS from the source in the residual graph to get levels.
2. DFS that only uses edges from level ℓ to ℓ + 1, with a per-node pointer `it[u]` so that
   dead edges are never retried. Push until blocked.
3. Repeat until the sink is unreachable.

O(V²E) in general, O(E √V) on unit-capacity bipartite graphs, and much faster than the
bound in practice. It is the one flow algorithm to type from memory.

## 3. Minimum cut

After the last BFS, let S = nodes reachable from the source in the residual graph. The
edges from S to outside S are saturated, and their total capacity equals the max flow.
*Police Chase*: undirected streets become two arcs of capacity 1 (in Dinic, one edge with
capacity 1 *and* reverse capacity 1). The answer is the max flow, and the streets to close
are those with exactly one endpoint in S.

## 4. Bipartite matching

Source → each boy (capacity 1), boy → girl for each allowed pair (1), each girl → sink (1).
Max flow = maximum matching. For small graphs, **Kuhn's algorithm** is shorter: for each
boy, DFS for an augmenting path that alternates unmatched and matched edges. O(VE).
*School Dance* uses it.

Useful corollaries:

- Minimum vertex cover = maximum matching (König), in bipartite graphs only.
- Maximum independent set = V − maximum matching, in bipartite graphs.
- Minimum path cover of a DAG by vertex-disjoint paths = V − maximum matching in the
  split graph (each node becomes an "out" copy and an "in" copy).

## 5. Recognising flow problems

Check the current [IOI syllabus](https://ioinformatics.org/page/syllabus/12) to see how
flows are classified this year. Either way, flow modelling appears in national olympiads
and on Codeforces, and matching arguments are useful in proofs. Signs:

- "Choose pairs / assign items to slots, each used at most once": matching.
- "Minimum number of things to delete to disconnect A from B": min cut (split each node
  into in/out with capacity 1 to cut **nodes** instead of edges).
- "Maximum number of disjoint routes": flow with unit capacities (*Distinct Routes*).
- Constraints are small: n ≤ 500, m ≤ 5000 is a strong hint.

## 6. Practice

1. CSES *Download Speed*, *Police Chase*, *School Dance* (reference solutions below).
2. CSES *Distinct Routes* (also print the routes: follow edges carrying flow).
3. Prove König's theorem from max-flow min-cut. It takes half a page and makes the
   corollaries above obvious.

Reference solutions: `solutions/cses/` (`download-speed`, `police-chase`, `school-dance`).
*Police Chase* and *School Dance* accept many outputs, so they have a `check.py`. Their
expected answers come from enumerating every cut or matching by brute force.

**Checkpoint:** Dinic from memory in under 20 minutes, and *Distinct Routes* accepted.
