# Phase B.4: Square-root decomposition and Mo's algorithm

*Months 4–6, [roadmap](../plan/after-30-days.md#phase-b-months-46-ioi-toolkit-part-1). About
one week.*

**Goal:** when no clever O(log n) structure comes to mind, split the input into √n blocks
and get O(√n) per operation. Answer offline range queries with Mo's algorithm.
**Math bridge:** a balancing argument. If one part of the cost is n/B and the other is B,
the sum is smallest at B = √n (AM–GM). The same balancing picks the block size in every
technique below, so derive it each time instead of memorising "√n".

**Read:** CPH ch. 27 · UG [Sqrt](https://usaco.guide/plat/sqrt) ·
CPA [sqrt decomposition](https://cp-algorithms.com/data_structures/sqrt_decomposition.html).

---

## 1. Blocks

Split the array into blocks of size B and store a summary per block (sum, min, a sorted
copy, a count array, …). A range query covers O(n/B) whole blocks plus at most 2B single
elements at the ends. A point update changes one element and one block summary. With
B ≈ √n both costs are O(√n).

Why learn this when segment trees exist? Because the block summary can be **anything**.
"How many elements in [l, r] are ≤ x, with point updates" is O(√n log n) with sorted
blocks, and it takes about 20 lines. The segment-tree solution needs a merge-sort tree or
a persistent tree.

## 2. Mo's algorithm

*Distinct Values Queries*: q queries "how many distinct values in a[l..r]?", all known
in advance (offline). Keep a window [L, R] with cnt[value] and the number of distinct
values. Moving either end by one step is O(1). Sort the queries so that the total
movement is small:

- Sort by (block of l, r), where the block of l is l / B.
- Within one block, R only moves forward: O(n) per block, O(n · n/B) in total.
- L moves at most B per query: O(q · B) in total.
- Balancing gives B = n / √q, and the total is O(n √q).

Implementation notes (see `solutions/cses/distinct-values-queries/sol.cpp`):

- Compress values to 0..n−1 first, so cnt is an array, not a `map`. A `map` adds a log
  factor to the inner loop and is the usual cause of TLE.
- Extend the window before shrinking it (`R++`, `L--`, then `R--`, `L++`). Otherwise the
  window can become "negative" and the counts go wrong.
- Sorting R in alternating directions in odd and even blocks often halves the running
  time.

Mo's algorithm needs the queries offline and an O(1) add/remove step. If the problem has
updates between queries, the variant "Mo with updates" uses B = n^(2/3).

## 3. Other √ tricks

- **Heavy/light by degree.** In a graph with m edges, at most √m nodes have degree
  > √m. Treat those "heavy" nodes specially. This is the standard way to count triangles in
  O(m √m).
- **Rebuild every √q operations.** Collect updates in a small buffer, answer queries using
  the last rebuilt structure plus the buffer, and rebuild when the buffer is full.
- **Small/large values.** For "jump by k" queries, precompute answers for k ≤ √n and
  simulate directly for k > √n (at most √n jumps).

## 4. Practice

1. CSES *Distinct Values Queries* with Mo's algorithm (reference solution below). Then
   solve it a second way: offline, sorted by right end, with a Fenwick tree that only
   counts the **last** occurrence of each value. That is O((n + q) log n).
2. CSES *Salary Queries* with sorted blocks.
3. A sqrt problem from UG [Sqrt](https://usaco.guide/plat/sqrt) problem list.

Reference solutions: `solutions/cses/distinct-values-queries`.

**Checkpoint:** derive the block size for Mo's algorithm from the cost formula, and pass
*Distinct Values Queries* with both methods. Time them on a max-size input.
