# Day 13: Dynamic programming II (knapsack, grids, sequences)

**Goal:** 2D states: grid paths, 0/1 knapsack, edit distance / LCS, plus LIS in O(N log N).
**Math bridge:** lattice-path counting (the grid DP is Pascal's rule with obstacles) and
Erdős–Szekeres (any sequence of n²+1 distinct numbers has a monotone subsequence of
length n+1), which is the theory behind LIS.

---

## 1. Grid paths (CSES *Grid Paths*, DP section)

paths[r][c] = paths[r−1][c] + paths[r][c−1], and 0 on a trap. Without traps this is
C(r+c, r), Pascal's rule. Check the start cell: if it is a trap, the answer is 0.

## 2. 0/1 knapsack (CSES *Book Shop*, AtCoder DP *D: Knapsack 1*)

State: best[i][w] = max value using the first i items with total weight ≤ w.
Transition: skip item i, or take it: best[i][w] = max(best[i−1][w], best[i−1][w−wᵢ] + vᵢ).

That is O(N·W) memory. Row i only reads row i−1, so keep one array and iterate **w
downwards**:

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> w = {3, 4, 5}, v = {30, 50, 60};
    int cap = 8;
    vector<long long> best(cap + 1, 0);
    for (int i = 0; i < 3; i++)
        for (int c = cap; c >= w[i]; c--)              // DOWNWARDS
            best[c] = max(best[c], best[c - w[i]] + v[i]);
    cout << best[cap] << "\n";                         // 90 (items 1 and 3)
}
```

Why downwards: when we update best[c] we read best[c − wᵢ], which must still hold the
row-(i−1) value. Going downwards, smaller indices are not yet overwritten. Going upwards,
item i could be used twice, which is exactly the *unbounded* knapsack (compare
Coin Combinations II, Day 12).

## 3. Array Description: DP over (position, value)

CSES *Array Description*: ways[i][v] = number of valid prefixes of length i ending in
value v. Then ways[i][v] = ways[i−1][v−1] + ways[i−1][v] + ways[i−1][v+1], restricted to
v = xᵢ when xᵢ is known. States n·m ≤ 10⁷, 3 transitions each: fine.

## 4. Two strings: edit distance and LCS

d[i][j] = edit distance between the first i letters of a and the first j letters of b.
Condition on what happens to the last letters:

- delete aᵢ: d[i−1][j] + 1
- insert bⱼ: d[i][j−1] + 1
- replace (free if equal): d[i−1][j−1] + [aᵢ ≠ bⱼ]

Base cases d[i][0] = i, d[0][j] = j. LCS is the same table with max instead of min. To
**print** an LCS (AtCoder DP *F*), keep the full table and walk back from (n, m):
whenever the letters match, that letter is in the answer.

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    string a = "LOVE", b = "MOVIE";
    int n = a.size(), m = b.size();
    vector<vector<int>> d(n + 1, vector<int>(m + 1));
    for (int i = 0; i <= n; i++) d[i][0] = i;
    for (int j = 0; j <= m; j++) d[0][j] = j;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            d[i][j] = min({d[i - 1][j] + 1, d[i][j - 1] + 1,
                           d[i - 1][j - 1] + (a[i - 1] != b[j - 1])});
    cout << d[n][m] << "\n";                           // 2
}
```

## 5. LIS in O(N log N)

Keep `tail[k]` = smallest possible last element of an increasing subsequence of length
k+1. It is sorted, so each new x replaces the first tail ≥ x (`lower_bound`), or extends the
array. The final size is the LIS length. Proof sketch: `tail` stays sorted and each entry is
optimal, by induction. Read UG [LIS](https://usaco.guide/gold/lis); practice on CSES
*Increasing Subsequence*.

## 6. Practice

1. CSES *Grid Paths* (DP section), *Book Shop*, *Array Description*, *Edit Distance*.
2. AtCoder DP *D: Knapsack 1*, *F: LCS*.
3. Read UG [Knapsack](https://usaco.guide/gold/knapsack),
   [Paths on Grids](https://usaco.guide/gold/paths-grids) and [LIS](https://usaco.guide/gold/lis).

Reference solutions: `solutions/cses/` (`grid-paths-dp`, `book-shop`, `array-description`,
`edit-distance`) and `solutions/atcoder-dp/` (`knapsack-1`, `lcs`).

**Checkpoint:** reduce knapsack memory from O(NW) to O(W) and explain why iterating W
downwards is required (and what upwards computes instead).
