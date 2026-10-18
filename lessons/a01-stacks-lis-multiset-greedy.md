# Phase A.1: Monotonic stacks, LIS, multiset greedy

*Months 2–3, [roadmap](../plan/after-30-days.md#phase-a-months-23-finish-the-core). About
one week.*

**Goal:** three small tools that come up all over the remaining CSES *Sorting and
Searching* and *Dynamic Programming* sections: the monotonic stack, the O(n log n) longest
increasing subsequence, and greedy choices made with `multiset::upper_bound`.
**Math bridge:** all three are **dominance** arguments. Once an element is beaten on every
criterion that matters for the future (older *and* larger, or the same length with a bigger
end), it can never be the answer again, so you delete it. Each element is deleted at most
once, so the total work is linear (amortised analysis, CPH ch. 8).

**Read:** CPH ch. 8 (amortised analysis: the stack argument) and ch. 7.3 (LIS).

---

## 1. Monotonic stack

*Nearest Smaller Values*: for each position, find the closest position to the left with a
smaller value. If j < k and x[j] ≥ x[k], then j is useless for every i > k: k is closer and
no larger. So the candidates, read from bottom to top of a stack, have strictly increasing
values. Before pushing i, pop everything ≥ x[i]. What remains on top is the answer.

```cpp
vector<int> st;                       // positions; values increase bottom -> top
for (int i = 1; i <= n; i++) {
    while (!st.empty() && x[st.back()] >= x[i]) st.pop_back();
    ans[i] = st.empty() ? 0 : st.back();
    st.push_back(i);
}
```

Every index is pushed once and popped at most once, so the loop is O(n) even though it
contains a `while`. This is a potential-function argument: the stack size is the potential,
and each pop is paid for by an earlier push.

Variants you will meet: nearest *greater* (flip the comparison), nearest on the *right*
(run the loop backwards), largest rectangle in a histogram (each bar's span is from its
nearest smaller on the left to its nearest smaller on the right). Using `>=` or `>` in the
pop condition decides how ties are treated. Decide that deliberately.

## 2. Longest increasing subsequence in O(n log n)

The quadratic DP from Day 13 (`best[i] = 1 + max best[j]` over j < i with x[j] < x[i]) is too
slow for n = 2·10⁵. Instead keep

> d[ℓ] = the smallest possible last element of an increasing subsequence of length ℓ + 1.

**Claim:** d is strictly increasing. (Proof: drop the last element of an optimal length-ℓ+2
subsequence. That gives a length-ℓ+1 subsequence whose last element is smaller.) So for each
new x, binary search the first d[ℓ] ≥ x and overwrite it with x. If there is none, append x.
The length of d is the answer.

`lower_bound` (first ≥ x) gives *strictly* increasing subsequences; `upper_bound` (first
> x) gives non-decreasing ones. d is **not** itself an increasing subsequence of the input,
only a table of best end values. Reconstructing an actual subsequence needs parent pointers.

## 3. Greedy with a multiset

*Towers*: cubes arrive in order. Each cube goes on a tower whose top is larger, or starts
a new tower. Greedy rule: put it on the tower with the **smallest top that is still
larger**. Exchange argument: if an optimal solution puts the cube on a tower with a larger
top, swap the two towers' futures. Every cube that could go on the larger top could also go
on the smaller one. In code this is `tops.upper_bound(k)` on a `multiset`, O(log n) per cube.

The same pattern ("give each item the smallest resource that fits") solves *Concert Tickets*
(Day 8), *Room Allocation* and *Movie Festival II*. Towers is LIS in disguise, too: by
Dilworth's theorem, the number of towers equals the length of the longest non-decreasing
subsequence.

## 4. Practice

1. CSES *Nearest Smaller Values*, *Towers*, *Increasing Subsequence* (reference solutions
   below).
2. CSES *Sorting and Searching*: *Room Allocation*, *Movie Festival II*, *Traffic Lights*,
   *Josephus Problem I*, *Nested Ranges Check*, *Array Division*, *Maximum Subarray Sum II*.
3. CSES *Sliding Window Problems*: *Sliding Window Minimum* (monotonic **deque**: pop
   dominated elements from the back, expired ones from the front).
4. Stress-test your LIS against the O(n²) DP (`make stress`) with values in [1, 3] so that
   ties are common.

Reference solutions: `solutions/cses/` (`nearest-smaller-values`, `towers`,
`increasing-subsequence`).

**Checkpoint:** explain in two sentences why the monotonic stack is O(n), and pass *Towers*
and *Increasing Subsequence* first try.
