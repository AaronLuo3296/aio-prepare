# Day 25: Bit manipulation and bitmask DP

**Goal:** use integers as sets, and run DP over all subsets when N ≤ 20.
**Math bridge:** subsets of {0, …, N−1} ↔ N-bit binary strings ↔ integers 0..2ᴺ−1, and
A ⊆ B ⇔ `(A & B) == A`. Subset DP is induction on |S|: if every proper subset is solved,
so is S. Iterating masks in increasing order is enough, since a proper subset of a mask
is always a smaller number.

---

## 1. The operations

| Set operation | Code |
|---------------|------|
| {i} | `1 << i` |
| i ∈ S? | `S >> i & 1` |
| S ∪ {i}, S \ {i} | `S \| 1 << i`, `S & ~(1 << i)` |
| toggle i | `S ^ 1 << i` |
| \|S\| | `__builtin_popcount(S)` (`__builtin_popcountll` for `long long`) |
| lowest element | `__builtin_ctz(S)` (S ≠ 0); lowest bit as a set: `S & -S` |
| full set | `(1 << n) - 1` |

**Precedence trap:** `==`, `&`, `^` and `|` bind *looser* than you expect.
`S & 1 << i == 0` parses as `S & ((1 << i) == 0)`. Use parentheses whenever you mix bit
operators with comparisons.

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n = 3;
    for (int S = 0; S < (1 << n); S++) {              // every subset of {0, 1, 2}
        cout << "{";
        for (int i = 0; i < n; i++)
            if (S >> i & 1) cout << " " << i;
        cout << " } size " << __builtin_popcount(S) << "\n";
    }
    int S = 0b1011;                                   // {0, 1, 3}
    for (int T = S; T > 0; T = (T - 1) & S)           // every nonempty subset of S
        cout << T << " ";
    cout << "\n";                                     // 11 10 9 8 3 2 1
}
```

Enumerating the submasks of every mask costs Σ 2^|S| = 3ᴺ in total (each element is "not
in S", "in S \ T" or "in T"). That is fine for N ≤ 15 and too slow for N = 20.

## 2. Hamiltonian paths

`dp[S][v]` = number of paths that start at vertex 0, visit exactly the set S, and end at
v ∈ S. Transition: dp[S][v] = Σ dp[S \ {v}][u] over edges u → v. There are 2ᴺ·N states and
each transition loops over up to N predecessors: **O(2ᴺ·N²)**. For N = 20 that is about
4·10⁸ simple steps, and pruning (masks must contain vertex 0; vertex N−1 only in the
full mask) cuts it by about 4×. CSES *Hamiltonian Flights* (count edges with
multiplicity). Memory: 2²⁰·20 ints = 80 MB, so declare the array **global**.

This is the TSP DP. With N! orderings, brute force dies at N ≈ 11. The DP forgets the
*order* inside S and remembers only the set and the endpoint.

## 3. Assignment-style DPs

- **Matching** (AtCoder DP *O*): `dp[S]` = ways to pair men 0..|S|−1 with exactly the
  women in S. Man |S| picks a woman not in S. O(2ᴺ·N). The trick: |S| tells you *which*
  man is next, so no second index is needed.
- **Elevator Rides** (CSES): `dp[S]` = the best (rides, weight of last ride) for the
  people in S, compared lexicographically. Fewer rides wins, then a lighter last ride.
  Adding a person either fits in the last ride or opens a new one. O(2ᴺ·N).

When you design the state, ask what the future needs to know about the past. For
Elevator Rides it needs the set of people still waiting and the space left in the
current ride. It does not need the earlier rides.

## 4. Practice

1. CSES *Hamiltonian Flights*, *Elevator Rides* · AtCoder DP *O: Matching*.
2. Read CPH ch. 10.
3. Redo CSES *Apple Division* (Day 5) by looping over masks instead of recursion.

Reference solutions: `solutions/cses/` (`hamiltonian-flights`, `elevator-rides`) and
`solutions/atcoder-dp/matching`.

**Checkpoint:** explain why *Hamiltonian Flights* is O(2ᴺ·N²), why that fits N = 20,
and why declaring `int dp[1 << 20][20]` inside `main` would crash
(the stack is usually only a few MB).
