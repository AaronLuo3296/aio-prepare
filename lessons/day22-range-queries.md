# Day 22: Fenwick trees, segment trees, sparse tables

**Goal:** answer range queries on an array that changes (point update, range query) in
O(log N), and static range minimum queries in O(1).
**Math bridge:** every positive integer i has a lowest set bit, `i & -i`. A Fenwick tree
splits the prefix [1, i] into blocks whose lengths are the powers of two in i's binary
expansion. For an idempotent operation (min(x, x) = x), two overlapping blocks cover a
range without double counting.

---

## 1. Which structure?

| Need | Structure | Build | Query | Update |
|------|-----------|-------|-------|--------|
| Static sums | prefix sums (Day 10) | O(N) | O(1) | — |
| Static min/max | sparse table | O(N log N) | O(1) | — |
| Sums + point updates | Fenwick tree | O(N) | O(log N) | O(log N) |
| Min, max, gcd, anything associative + updates | segment tree | O(N) | O(log N) | O(log N) |

Prefix tricks need an **inverse** (sum has subtraction, xor is its own inverse). Min has
no inverse, so min queries need one of the other structures. That is why CSES *Range Xor
Queries* is just prefix sums with `^` in place of `+` and `-`.

## 2. Fenwick tree (binary indexed tree)

Node i stores the sum of the `i & -i` elements ending at position i (1-indexed).
`prefix(i)` strips the lowest bit until 0; `add(i)` adds the lowest bit until past N.
Each loop runs once per bit: O(log N).

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Fenwick {
    int n;
    vector<ll> t;
    Fenwick(int n) : n(n), t(n + 1, 0) {}
    void add(int i, ll d) {
        for (; i <= n; i += i & -i) t[i] += d;
    }
    ll prefix(int i) {                // sum of positions 1..i
        ll s = 0;
        for (; i > 0; i -= i & -i) s += t[i];
        return s;
    }
    ll range(int l, int r) { return prefix(r) - prefix(l - 1); }
};

int main() {
    vector<ll> a = {0, 3, 2, 4, 5, 1, 1, 5, 3};   // a[1..8]; a[0] unused
    Fenwick f(8);
    for (int i = 1; i <= 8; i++) f.add(i, a[i]);
    cout << f.range(1, 4) << "\n";                // 14
    f.add(3, 1 - a[3]);                           // set a[3] = 1: add the difference
    a[3] = 1;
    cout << f.range(1, 4) << "\n";                // 11
}
```

Trace `prefix(7)` by hand: 7 = 111₂ → nodes 7 (length 1), 6 (length 2), 4 (length 4),
which cover [7,7], [5,6] and [1,4].

## 3. Segment tree, bottom-up

Store the leaves at `t[n..2n-1]`, and set node i = op(t[2i], t[2i+1]) for i = n−1 down
to 1. To query [l, r), move both ends up one level at a time. When l is a right child,
its parent's range sticks out to the left of the query, so take t[l] itself and step
right. Handle r the same way, mirrored. CSES *Dynamic Range Minimum Queries*
(`solutions/cses/dynamic-range-minimum-queries/sol.cpp`) is about 15 lines this way, and
it works for any n, not only powers of two.

The recursive, top-down segment tree is longer but extends to *lazy propagation* (range
updates), covered after Day 30. Learn bottom-up now, because it is what you will type
under time pressure.

## 4. Sparse table

`sp[j][i]` = min of a[i .. i + 2ʲ − 1], built by sp[j][i] = min(sp[j−1][i],
sp[j−1][i + 2ʲ⁻¹]). For a query of length L, let k = ⌊log₂ L⌋. The two blocks of length
2ᵏ starting at l and ending at r overlap but cover [l, r] exactly. Compute k with
`31 - __builtin_clz(L)` (`__lg` is GCC-only).

## 5. Practice

1. CSES *Static Range Minimum Queries* (sparse table), *Dynamic Range Sum Queries*
   (Fenwick), *Dynamic Range Minimum Queries* (segment tree), *Range Xor Queries*.
2. Read CPH ch. 9 and the first half of ch. 28.
3. Stress-test your segment tree against a brute force that loops over the range
   (`make stress`, Day 7).

Reference solutions: `solutions/cses/` (`static-range-minimum-queries`,
`dynamic-range-sum-queries`, `dynamic-range-minimum-queries`, `range-xor-queries`).

**Checkpoint:** write a bottom-up segment tree from memory in under 15 minutes, and pass
*Dynamic Range Minimum Queries* with it.
