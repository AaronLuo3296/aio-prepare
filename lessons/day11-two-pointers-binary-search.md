# Day 11: Two pointers and binary search

**Goal:** two pointers on arrays where a window only ever moves right, and binary search on
a monotone yes/no question ("binary search the answer").
**Math bridge:** monotone functions and bisection. If a predicate is false, false, …,
false, true, true, …, the switch point can be found in log₂(range) questions, just like
the intermediate value theorem's bisection proof.

---

## 1. Two pointers

When the best left end l(r) for each right end r never decreases, move both ends forward.
Each pointer moves at most n times, so the total work is O(n), not O(n²). This is an
amortised argument (CPH ch. 8).

CSES *Playlist* (longest block with no repeated song): for each r, l is the first index
such that a[l..r] has no repeat. When a[r] was last seen at position p ≥ l, jump l to p+1.

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> k = {1, 2, 1, 3, 2, 7, 4, 2};
    map<int, int> last;
    int l = 0, best = 0;
    for (int r = 0; r < (int)k.size(); r++) {
        if (last.count(k[r])) l = max(l, last[k[r]] + 1);
        last[k[r]] = r;
        best = max(best, r - l + 1);
    }
    cout << best << "\n";                  // 5: the block 1 3 2 7 4
}
```

Other uses: *Sum of Two Values* (sort, then move ends inward), *Subarray Sums I* (positive
numbers only, so the window sum is monotone).

## 2. Kadane's algorithm (CSES *Maximum Subarray Sum*)

Let E(i) = best sum of a subarray **ending at** i. Then E(i) = max(aᵢ, E(i−1) + aᵢ), and the
answer is maxᵢ E(i). Proof by induction on i. This is your first DP; Day 12 builds on it.
Edge case: if all numbers are negative, the answer is the largest one, not 0.

## 3. Binary search with an invariant

Write every binary search the same way, and it will never loop forever:

> **Invariant:** `lo` is always bad (false), `hi` is always good (true).
> Loop while `hi − lo > 1`. The answer is `hi`.

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    // smallest x with x*x >= 2'000'000'000
    auto good = [](ll x) { return x * x >= 2'000'000'000LL; };
    ll lo = 0, hi = 2'000'000'000;           // good(0) is false, good(hi) is true
    while (hi - lo > 1) {
        ll mid = lo + (hi - lo) / 2;
        if (good(mid)) hi = mid; else lo = mid;
    }
    cout << hi << "\n";                      // 44722
}
```

Before coding, check the endpoints really satisfy the invariant. For searching a sorted
array use `lower_bound` / `upper_bound` from Day 8 instead.

## 4. Worked problem: CSES *Factory Machines*

> n machines; machine i makes one product every kᵢ seconds. Least time to make t products?

"Can we make t products in T seconds?" ⇔ Σ ⌊T/kᵢ⌋ ≥ t. This is monotone in T, so binary
search T with `lo = 0` (bad) and `hi = min(k)·t` (good: the fastest machine alone suffices).
`hi` reaches 10¹⁸, which still fits in `long long` (max ≈ 9.2·10¹⁸). The sum Σ ⌊T/kᵢ⌋ can
overflow, so stop adding as soon as it reaches t.

## 5. Practice

1. CSES *Sum of Two Values*, *Maximum Subarray Sum*, *Playlist*, *Factory Machines*.
2. Read UG [Two Pointers](https://usaco.guide/silver/two-pointers),
   UG [Binary Search](https://usaco.guide/silver/binary-search) and
   CPA [Binary search](https://cp-algorithms.com/num_methods/binary_search.html).
   Watch an [Errichto](https://www.youtube.com/@Errichto) binary search lecture.

Reference solutions: `solutions/cses/` (`sum-of-two-values`, `maximum-subarray-sum`,
`playlist`, `factory-machines`).

**Checkpoint:** write the lo-bad / hi-good binary search from memory, and prove that the
loop terminates.
