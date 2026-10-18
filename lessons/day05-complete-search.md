# Day 5: Simulation and complete search

**Goal:** turn a statement into code faithfully, and when the search space is small,
check *every* case.
**Math bridge:** exhaustive case analysis. On paper it is tedious. In code, 2²⁰ ≈ 10⁶
cases takes milliseconds. The skill is **counting the cases first** to know whether it fits.

---

## 1. Simulation

Many easy AIO problems (and most first subtasks) just ask you to *do what the statement
says*. Read twice, write down the state, update it exactly as described. Typical bugs are
misread rules and off-by-one boundaries, so test on the sample *and* on tiny cases you
compute by hand. Read UG [Simulation](https://usaco.guide/bronze/simulation).

## 2. Bit operations (needed for subsets)

| Expression | Meaning |
|------------|---------|
| `1 << k` | 2ᵏ |
| `mask >> i & 1` | bit i of mask (0 or 1) |
| `mask \| (1 << i)` | set bit i |
| `mask & ~(1 << i)` | clear bit i |
| `a ^ b` | XOR |
| `__builtin_popcount(mask)` | number of 1 bits |

Read UG [Intro to Bitwise Operations](https://usaco.guide/bronze/intro-bitwise) if this is new.

## 3. All subsets with a bitmask

The subsets of {0, …, n−1} correspond to the integers 0 … 2ⁿ − 1 (binary representation =
characteristic vector, a bijection you know):

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n = 3;
    for (int mask = 0; mask < (1 << n); mask++) {
        cout << "{";
        for (int i = 0; i < n; i++)
            if (mask >> i & 1) cout << " " << i;
        cout << " }\n";
    }
}
```

Cost: 2ⁿ · n. For n = 20 that is ≈ 2 · 10⁷, comfortably fast.

## 4. All permutations

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s = "bca";
    sort(s.begin(), s.end());          // MUST start from the smallest arrangement
    do {
        cout << s << "\n";             // abc acb bac bca cab cba
    } while (next_permutation(s.begin(), s.end()));
}
```

`next_permutation` rearranges into the next lexicographic order and returns `false` after
the last one. Repeated letters are handled automatically: each *distinct* arrangement
appears once. Cost: n! · n, fine for n ≤ 8–10.

## 5. Worked problem: CSES *Apple Division*

> Split n ≤ 20 apples with weights up to 10⁹ into two groups minimising the weight
> difference.

1. Constraint n ≤ 20 points to subsets.
2. For each mask, group 1 = apples whose bit is set, so difference = |total − 2·group|.
3. Weights sum to 2 · 10¹⁰, so use `long long`.

Could you halve the work? (Mask and its complement give the same difference.) Does it
matter here? (No. Don't optimise what already fits.)

## 6. Practice

1. ORAC *Starter Set IV*.
2. CSES *Apple Division*, *Creating Strings*.
3. Read CPH ch. 5.1–5.2 and UG [Basic Complete Search](https://usaco.guide/bronze/intro-complete).

**Checkpoint:** write the subset-enumeration loop from memory, and state the largest n for
which subset search and permutation search fit in 1 second.
