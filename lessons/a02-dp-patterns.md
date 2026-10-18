# Phase A.2: DP patterns: intervals, digits, rerooting

*Months 2–3, [roadmap](../plan/after-30-days.md#phase-a-months-23-finish-the-core). About
one to two weeks, alongside the rest of the CSES DP section and AtCoder DP.*

**Goal:** recognise three DP *shapes* that the bootcamp did not cover: DP over intervals,
DP over the digits of a number, and computing a tree DP for **every** root at once.
**Math bridge:** interval DP is strong induction on the interval length. Digit DP is
counting by the first position where you fall below the bound, the same case split you use
to count the integers ≤ N with some property by hand. Rerooting is the identity
f(child) = f(parent) + (change) that you would use to sum distances by hand.

**Read:** CPH ch. 7, ch. 14.3 (all longest paths, which is rerooting) · UG
[Gold](https://usaco.guide/gold) DP modules.

---

## 1. Interval DP

State: a contiguous piece x[l..r]. The transition removes or splits off something at the
ends. Order: by increasing length, so that every sub-interval is ready.

*Removal Game*: players alternately take the first or last number. Track the **difference**
d[l][r] = (score of the player to move) − (score of the other) on x[l..r]:

    d[l][r] = max( x[l] − d[l+1][r],  x[r] − d[l][r−1] ),   d[i][i] = x[i].

This is the zero-sum trick: after your move the roles swap, so the opponent's best
difference enters with a minus sign. First player's score = (total + d[0][n−1]) / 2.

**Memory.** n = 5000 means 25·10⁶ states. As `long long` that is 200 MB, over the limit.
Since d[·][r] needs only d[·][r−1], keep one row. Read the reference solution for the loop
order that makes a single array work. Always do the memory arithmetic (states × bytes)
before you write the table.

Other interval DPs: *Rectangle Cutting* (2D splits), matrix-chain style "merge adjacent
piles" (cost depends on the split point), palindromic subsequences.

## 2. Digit DP

"Count v in [a, b] with property P" becomes f(b) − f(a − 1), where f(x) counts [0, x].
Write x as a digit string and walk it left to right. At position i you either copy x's
digit (still **tight**) or place a smaller digit, and then every later position is free.
The state is (position, tight?, whatever P needs to remember, e.g. the previous digit).

*Counting Numbers* (no two equal adjacent digits): once you go below x at position i, each
of the remaining L − 1 − i positions has exactly 9 choices (anything but its left neighbour),
so you add 9^(L−1−i) for each allowed smaller digit. Numbers with fewer digits than x are
counted separately. Most of the bugs are at the edges:

- f(−1) when a = 0, and leading zeros (is "007" the number 7, with digits 0,0,7?).
- If x's own prefix already breaks P, stop: no later tight choice can fix it.
- Test against a brute force over every v up to a few thousand. This is the one DP where
  that test is nearly mandatory.

For harder properties (digit sum divisible by k, contains "13"), memoise
`go(pos, tight, state)` recursively. There are only ~20 positions.

## 3. Rerooting (all roots at once)

*Tree Distances II*: for every node, the sum of distances to all others. One DFS from each
root is O(n²). Instead:

1. Root at 1 and compute subtree sizes sz[v] and ans[1] = sum of depths.
2. Moving the root across the edge p → v brings the sz[v] nodes of v's subtree one step
   closer, and pushes the other n − sz[v] one step further:
   ans[v] = ans[p] + n − 2·sz[v].
3. A second pass from the root (parents before children) fills every ans[v]. O(n).

The general recipe: compute "down" values (inside the subtree), then "up" values (the
rest of the tree, seen from v) from the parent's up value and the siblings' down values.
When the operation has no inverse (e.g. max), use prefix and suffix maxima over the
children instead of subtracting.

Trees of 2·10⁵ nodes can be paths, and recursive DFS on a path can overflow the stack
(Day 20). The reference solution uses an explicit stack to get a parents-first order, then
loops over that order forwards and backwards. Learn this pattern. It is used again in
Phase C.

## 4. Practice

1. CSES *Removal Game*, *Counting Numbers*, *Tree Distances II* (reference solutions below).
2. CSES *Dynamic Programming*: *Rectangle Cutting*, *Money Sums*, *Two Sets II*,
   *Projects* (sort + binary search + DP), *Counting Towers*, *Increasing Subsequence II*
   (DP + Fenwick tree).
3. AtCoder DP: *N – Slimes* (interval), *S – Digit Sum* (digit), *V – Subtree* (rerooting
   without inverses).
4. Finish the rest of the [AtCoder Educational DP Contest](https://atcoder.jp/contests/dp).
   Leave *Z – Frog 3* for [Phase C.3](c03-dp-optimisations.md).

Reference solutions: `solutions/cses/` (`removal-game`, `counting-numbers`,
`tree-distances-ii`).

**Checkpoint:** for each of the three shapes, state the DP (state, transition, order,
memory) in writing before coding, and get *Counting Numbers* accepted with f(0), f(9) and
f(10) checked by hand.
