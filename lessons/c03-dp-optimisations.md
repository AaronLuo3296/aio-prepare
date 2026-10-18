# Phase C.3: DP optimisations: convex hull trick, divide and conquer, bitset

*Months 7–12, [roadmap](../plan/after-30-days.md#phase-c-months-712-ioi-toolkit-part-2-and-full-past-papers).
About three weeks. Many IOI subtasks are "the O(n²) DP", and the last subtask is the same
DP made faster.*

**Goal:** take a correct but slow DP and speed up its transition: the convex hull trick
for transitions of the form min over j of (a_j · x_i + b_j), divide and conquer when the
optimal split point is monotone, and bitsets for boolean DPs.
**Math bridge:** a minimum of linear functions is a concave piecewise-linear function,
the lower envelope. Its pieces appear in slope order, which is why a deque suffices.
Monotone split points come from the quadrangle inequality
C(a, c) + C(b, d) ≤ C(a, d) + C(b, c) for a ≤ b ≤ c ≤ d, an exchange argument in
disguise. A bitset is a vector over GF(2) packed into machine words, so 64 updates happen
in one instruction.

**Read:** CPA [convex hull trick](https://cp-algorithms.com/geometry/convex_hull_trick.html),
[divide and conquer DP](https://cp-algorithms.com/dynamic_programming/divide-and-conquer-dp.html) ·
UG [Platinum](https://usaco.guide/plat) (Convex Hull Trick, and the DP modules).

---

## 1. Write the slow DP first

Always start with the O(n²) or O(kn²) DP, prove it, and submit it for the subtasks. Then
look at the **shape of the transition**:

| Transition | Optimisation |
|------------|--------------|
| dp[i] = min_j (dp[j] + a_j · x_i + b_j) | convex hull trick |
| dp[k][i] = min_{j<i} (dp[k−1][j] + C(j, i)), opt(i) monotone | divide and conquer |
| boolean reachability, subset sums | bitset |
| dp[i] = min over a sliding window of j | monotonic deque ([A.1](a01-stacks-lis-multiset-greedy.md)) |

The slow DP is also your stress-test reference for the fast one.

## 2. Convex hull trick

*Frog 3* (AtCoder DP Z): dp[i] = min_j dp[j] + (h_i − h_j)² + C. Expand the square:

    dp[i] = h_i² + C + min_j ( (−2 h_j) · h_i + (dp[j] + h_j²) ).

Each j contributes a **line** with slope −2h_j and intercept dp[j] + h_j², evaluated at
x = h_i. We need the lowest line at x.

- h is increasing, so the slopes arrive in **decreasing** order and the queries in
  **increasing** order. Then a deque works: new lines go on the back after popping
  lines that are no longer on the envelope, and the query pointer only moves forward.
  O(n) total. The `MonotoneCHT` struct in `solutions/atcoder-dp/frog-3/sol.cpp` is
  reused unchanged in *Monster Game I*.
- The test "is the middle line useless?" compares two intersection points. Cross-multiply
  instead of dividing. The products can exceed 10¹⁸, so use `__int128` (or `long double`
  with care).
- Equal slopes: keep only the lower line, or the intersection test divides by zero.
- Queries not monotone: binary search on the hull, O(log n) each.
- Slopes not monotone either: **Li Chao tree** (a segment tree over x that stores one line
  per node), O(log C) per insert and query. It is easier to get right than a dynamic hull.

## 3. Divide and conquer optimisation

*Subarray Squares*: split n numbers into k parts minimising the sum of (part sum)².
dp[j][i] = min_{p<i} dp[j−1][p] + (P[i] − P[p])². The cost satisfies the quadrangle
inequality, so opt(i), the best p, is non-decreasing in i. Compute the middle i of a range
by scanning [optl, optr], then recurse: the left half needs only [optl, opt(mid)], the
right half only [opt(mid), optr]. Each level of the recursion scans O(n), so a layer
costs O(n log n) and the whole DP O(kn log n).

If you cannot prove the monotonicity, check it empirically: print opt(i) from the slow DP
on random inputs. That is acceptable in contest. Prove it afterwards.

## 4. Bitset

`bitset<N> b;` supports shifts, `|`, `&` and `count()` 64 bits at a time. Subset sum
over n items with total S: `b |= b << w` for each weight w, so O(nS/64). Reachability on a
DAG with n = 5·10⁴: each node's reachable set is the OR of its successors' sets, so
O(n m / 64) time and n²/8 bytes of memory. Do that memory arithmetic before you start.

## 5. Practice

1. AtCoder DP *Z – Frog 3*, CSES *Monster Game I*, *Subarray Squares* (reference solutions
   below).
2. CSES *Monster Game II* (queries not monotone: Li Chao tree), *Houses and Schools*
   (divide and conquer), *Knuth Division* (Knuth's optimisation), *Reachable Nodes* and
   *Reachability Queries* (bitset).
3. IOI 2016 *Aliens* or IOI 2014 *Holiday* on [oj.uz](https://oj.uz/problems/source/22),
   after the CSES ones. Expect to spend several sessions on each.

Reference solutions: `solutions/atcoder-dp/frog-3`, `solutions/cses/` (`monster-game-i`,
`subarray-squares`). *Monster Game I* and *Subarray Squares* are tested against brute
force over all choices. *Frog 3* is tested against the O(n²) DP and the three official
samples.

**Checkpoint:** for each of the three techniques, take a slow DP you wrote earlier, apply
the optimisation, and stress-test the two against each other.
