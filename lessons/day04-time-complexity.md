# Day 4: Time complexity and reading constraints

**Goal:** predict whether a solution is fast enough **before** writing it.
**Math bridge:** big-O is the asymptotics you already use. Counting operations is a
counting problem, usually solved by double counting or a known sum.

---

## 1. The budget

A judge machine does roughly **10⁸ simple operations per second**. Time limits are usually
1 second. So the constraints tell you which complexity the intended solution has:

| n up to | Feasible complexity | Typical technique |
|---------|---------------------|-------------------|
| 10 | O(n!) | try all permutations |
| 20 | O(2ⁿ · n) | try all subsets (bitmasks) |
| 500 | O(n³) | triple loop, Floyd–Warshall |
| 5 000 | O(n²) | double loop, 2D DP |
| 2 · 10⁵ | O(n log n) | sorting, binary search, segment trees |
| 10⁷ | O(n) | one pass, prefix sums |
| 10¹⁸ | O(log n) or O(1) | formula, binary search, fast exponentiation |

**Habit:** read the constraints *first*. They tell you what complexity to aim for.

## 2. Counting operations

| Code shape | Operations | Why |
|------------|------------|-----|
| one loop to n | n | |
| `for i < n: for j < n` | n² | product rule |
| `for i < n: for j < i` | n(n−1)/2 = O(n²) | Gauss |
| `for i in 1..n: for j = i; j <= n; j += i` | n/1 + n/2 + … + n/n ≈ n ln n | harmonic series |
| `while (n > 0) n /= 2` | log₂ n | halving |
| all subsets of n items, O(n) work each | 2ⁿ · n | |

The harmonic line is worth memorising: it is why the sieve of Eratosthenes and
"loop over all multiples" ideas are fast.

## 3. Modular arithmetic in code

"Print the answer modulo 10⁹ + 7" appears constantly. The rules are the ones you know:
(a + b) mod m and (a · b) mod m depend only on a mod m and b mod m. In code, **reduce
after every operation** so numbers stay small:

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll MOD = 1'000'000'007;

int main() {
    int n;
    cin >> n;
    ll ans = 1;
    for (int i = 0; i < n; i++) ans = ans * 2 % MOD;   // ans < MOD, so ans*2 fits easily
    cout << ans << "\n";
}
```

Two residues below ~10⁹ multiply to < 10¹⁸ < 2⁶³, so `long long` is safe for one product.
Two `int` residues multiplied as `int` overflow.

## 4. Fast input/output

With 10⁵+ numbers, default C++ streams can be slow. These two lines at the top of `main`
fix it (they are in the template):

```cpp
ios::sync_with_stdio(false);
cin.tie(nullptr);
```

Prefer `"\n"` over `endl` (`endl` flushes output every time, which is slow). After these
lines, don't mix `cin`/`cout` with `scanf`/`printf`. See UG [Fast I/O](https://usaco.guide/general/fast-io).

## 5. Worked problem: CSES *Two Sets*

> Split {1, …, n} into two sets of equal sum, or report that it's impossible. n ≤ 10⁶.

- **Necessary:** n(n+1)/2 must be even.
- **Sufficient:** let T = n(n+1)/4. Go from n down to 1, putting i in the first set
  whenever i ≤ (remaining target). Claim: this hits T exactly. (Proof idea: every integer in
  [0, n(n+1)/2] is a subset sum of {1..n}. Show the greedy maintains "remaining target ≤
  1 + 2 + … + i". Write the induction.)
- **Complexity:** O(n), fine for 10⁶. Output is up to 10⁶ numbers, so fast I/O matters.

Also today: *Bit Strings* (2ⁿ mod p), *Coin Piles* (find the invariant: each move removes
3 coins and changes a − b by ±1), *Gray Code* (`i ^ (i >> 1)`. Prove consecutive codes
differ in one bit).

## 6. Practice

1. CSES *Bit Strings*, *Coin Piles*, *Two Sets*, *Gray Code*.
2. Read CPH ch. 2 and UG [Time Complexity](https://usaco.guide/bronze/time-comp).
3. Watch 6.006 Lecture 1 ([lecture videos](https://ocw.mit.edu/courses/6-006-introduction-to-algorithms-spring-2020/video_galleries/lecture-videos/)).

**Checkpoint:** for every problem solved so far, write its complexity and the largest n it
could handle in 1 second.
