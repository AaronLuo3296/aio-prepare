# Phase B.3: Lazy propagation and segment tree variants

*Months 4–6, [roadmap](../plan/after-30-days.md#phase-b-months-46-ioi-toolkit-part-1). About
two weeks. Segment trees are the most common data structure in IOI tasks.*

**Goal:** range updates **and** range queries in O(log n), find the first position
satisfying a condition by descending the tree, and know the main variants.
**Math bridge:** lazy propagation needs updates that form a **monoid acting on** the
node values. Two updates must compose into one update ("add 3 then add 5" = "add 8";
"set to 4 then add 2" = "set to 6"), and an update must be applicable to a node's summary
without looking at its children (sum += x · length). If you can write those two rules
down, the tree works.

**Read:** CPH ch. 28 · UG [Segment Tree extensions](https://usaco.guide/plat/segtree-ext) ·
CPA [segment tree](https://cp-algorithms.com/data_structures/segment_tree.html).

---

## 1. Range update, point query: no lazy needed

*Range Update Queries*: add u to a[a..b], ask for a[k]. Store the **difference array**
d[i] = a[i] − a[i−1] in a Fenwick tree (Day 22). A range add touches two entries of d, and
a[k] is a prefix sum of d. Before reaching for lazy propagation, check whether a
difference array already turns the problem into point updates.

## 2. Lazy propagation

The recursive tree from CPH ch. 28: node v covers [l, r]. A range update that fully covers
a node **stops there**. It updates the node's summary and stores a pending tag. Any later
visit that needs to go below the node first calls `push`, which hands the tag to both
children. Each operation touches O(log n) nodes, as for a plain query.

*Range Updates and Sums* has two kinds of update, "add x" and "set to x". The tags are
(has_set, set_value, add_value), meaning "first set (if has_set), then add":

| New update arrives | Effect on the stored tag | Effect on the sum (length len) |
|--------------------|--------------------------|--------------------------------|
| set x | has_set = true, set_value = x, add_value = 0 | sum = x · len |
| add x | add_value += x | sum += x · len |

Write this table **before** coding any lazy tree with more than one update type. Most
lazy bugs are composition bugs: the order of tags is applied the wrong way round, or a
`set` forgets to clear the pending `add`.

Debugging checklist:

- Every function that recurses into the children calls `push` first. That includes
  queries.
- After recursing, recompute the node from its children (`pull`).
- The tree has 4n nodes. 2n is only enough for the bottom-up version.
- Stress-test against a naive array with n ≤ 10 and many random operations. The reference
  tests do exactly that.

## 3. Descending the tree

*Hotel Queries*: find the **first** hotel with at least r free rooms. Binary search over
prefix maxima costs O(log² n). Instead, descend from the root: go left if the left child's
max is ≥ r, otherwise go right. That is O(log n). The same descent answers "k-th one in a
0/1 array" (*List Removals*), and "first prefix sum ≥ s".

## 4. Variants worth knowing (UG Platinum)

| Variant | Idea | CSES example |
|---------|------|--------------|
| Node stores several values | max subarray sum: store (sum, best prefix, best suffix, best) and merge | *Subarray Sum Queries* |
| Arithmetic-progression update | lazy tag (first term, difference); progressions add | *Polynomial Queries* |
| Persistent | copy only the O(log n) changed nodes per update | *Range Queries and Copies* |
| Offline sweep + Fenwick | sort queries by right end, process the array once | *Distinct Values Queries* (see [B.4](b04-sqrt-decomposition.md)) |
| 2D | Fenwick of Fenwicks, or offline | *Forest Queries II* |

## 5. Practice

1. CSES *Range Update Queries*, *Range Updates and Sums*, *Hotel Queries* (reference
   solutions below).
2. CSES *List Removals*, *Salary Queries* (compress coordinates offline, or use an
   order-statistics structure), *Prefix Sum Queries*, *Subarray Sum Queries*,
   *Polynomial Queries*.
3. Type a lazy segment tree (add + sum) from memory until it takes under 15 minutes.

Reference solutions: `solutions/cses/` (`range-update-queries`, `range-updates-and-sums`,
`hotel-queries`).

**Checkpoint:** write the composition table for "add + set" and for "add arithmetic
progression", and get *Range Updates and Sums* accepted.
