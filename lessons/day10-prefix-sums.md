# Day 10: Prefix sums and difference arrays

**Goal:** answer "sum of a[l..r]" in O(1) after O(N) preprocessing, in 1D and 2D, and count
subarrays with a given sum.
**Math bridge:** telescoping sums, and the pigeonhole lemma "among n integers, some
non-empty block of consecutive ones has sum divisible by n" (prefix sums mod n).

---

## 1. Prefix sums

Define P[0] = 0 and P[i] = a₁ + … + aᵢ. Then a_l + … + a_r = P[r] − P[l−1] (telescoping).
Use **1-based** arrays here: P[l−1] then needs no special case for l = 1.

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n = 8;
    vector<ll> a = {0, 3, 2, 4, 5, 1, 1, 5, 3};      // a[0] unused: 1-based
    vector<ll> P(n + 1, 0);
    for (int i = 1; i <= n; i++) P[i] = P[i - 1] + a[i];
    cout << P[4] - P[1] << "\n";                     // a2 + a3 + a4 = 11
}
```

This is CSES *Static Range Sum Queries*. Values go up to 10⁹, so sums need `long long`.

## 2. Difference arrays (the inverse operation)

To add v to every a[l..r] many times and read the array only at the end: set
D[l] += v, D[r+1] −= v, then take prefix sums of D. Prefix sum and difference are inverse
operations, the discrete version of integration and differentiation.

## 3. 2D prefix sums

P[i][j] = sum of the rectangle (1,1)…(i,j). By inclusion–exclusion:

- build: P[i][j] = a[i][j] + P[i−1][j] + P[i][j−1] − P[i−1][j−1]
- query (r₁,c₁)…(r₂,c₂): P[r₂][c₂] − P[r₁−1][c₂] − P[r₂][c₁−1] + P[r₁−1][c₁−1]

Practice: CSES *Forest Queries*.

## 4. Counting subarrays with sum x

A subarray (l, r] has sum P[r] − P[l]. So for each r we need **the number of earlier
prefix sums equal to P[r] − x**. Keep a `map` from prefix-sum value to count:

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    vector<ll> a = {2, -1, 3, 5, -2};
    ll x = 7;
    map<ll, int> seen;
    seen[0] = 1;                       // the empty prefix P[0] = 0
    ll prefix = 0, count = 0;
    for (ll v : a) {
        prefix += v;
        if (seen.count(prefix - x)) count += seen[prefix - x];
        seen[prefix]++;
    }
    cout << count << "\n";             // 2
}
```

This solves CSES *Subarray Sums I* and *II*. Negative numbers are fine.

## 5. Worked problem: CSES *Subarray Divisibility*

n divides P[r] − P[l] exactly when P[r] ≡ P[l] (mod n). So count pairs of equal residues
among P[0], …, P[n]. If residue k occurs c_k times, the answer is Σ c_k(c_k − 1)/2. That
is the pigeonhole lemma made quantitative: n+1 prefix sums, n residues, so there is at least
one pair.

C++ trap: `-7 % 3 == -1`. Normalise with `((x % n) + n) % n`.

## 6. Practice

1. CSES *Static Range Sum Queries*, *Subarray Sums I*, *Subarray Sums II*,
   *Subarray Divisibility*. Optional: *Forest Queries* (2D).
2. Read UG [Prefix Sums](https://usaco.guide/silver/prefix-sums) and CPH ch. 9.1.

Reference solutions: `solutions/cses/` (`static-range-sum-queries`, `subarray-sums-i`,
`subarray-sums-ii`, `subarray-divisibility`).

**Checkpoint:** solve *Subarray Divisibility* and name the classical olympiad lemma it uses.
