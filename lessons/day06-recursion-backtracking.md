# Day 6: Recursion and backtracking

**Goal:** write functions that call themselves. Generate subsets and permutations
recursively. Prune a search.
**Math bridge:** recursion *is* strong induction. To prove `f(n)` correct, assume every
smaller call is correct (the inductive hypothesis) and check the base case. You never need
to trace the whole call tree, just as you never unroll an induction proof.

---

## 1. A recursive function

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll factorial(int n) {
    if (n == 0) return 1;            // base case: stops the recursion
    return n * factorial(n - 1);     // smaller instance
}

int main() {
    cout << factorial(20) << "\n";   // 2432902008176640000 (21! overflows long long)
}
```

Each call gets its own copy of local variables on the **call stack**. Missing or
unreachable base case → infinite recursion → crash (RE). Recursion depth of ~10⁵–10⁶ can
also crash on some judges. Keep that in mind for later graph problems.

## 2. Generating choices recursively

The **backtracking** pattern: make a choice, recurse, *undo the choice*.

```cpp
#include <bits/stdc++.h>
using namespace std;

int n = 3;
vector<int> chosen;
vector<bool> used(n, false);

void permute() {
    if ((int)chosen.size() == n) {           // a complete permutation
        for (int x : chosen) cout << x << " ";
        cout << "\n";
        return;
    }
    for (int i = 0; i < n; i++) {
        if (used[i]) continue;
        used[i] = true;  chosen.push_back(i);    // choose
        permute();                               // explore
        used[i] = false; chosen.pop_back();      // un-choose
    }
}

int main() { permute(); }
```

Subsets work the same way with two branches per element (take it / skip it).

## 3. Pruning

Backtracking beats brute force when you **abandon a branch as soon as it cannot succeed**.
For n queens, place one queen per row, and before recursing check that its column and both
diagonals are free. Diagonals are lines r + c = const and r − c = const (shift r − c by
+7 to use it as an array index). Each check is O(1) with three boolean arrays.

## 4. Worked problem: CSES *Chessboard and Queens*

> Count placements of 8 non-attacking queens on an 8 × 8 board where some squares are
> blocked (`*`).

Row-by-row backtracking with column/diagonal arrays. Skip blocked squares. The answer
is a small number (≤ 92), and the search visits only a few thousand nodes. Verify with the
empty board: you must get 92.

## 5. Worked problem: CSES *Tower of Hanoi*

Recursive structure: to move n disks from 1 to 3, move n−1 disks to 2, move the largest to
3, move n−1 from 2 to 3. Prove by induction that this uses 2ⁿ − 1 moves and that no
solution uses fewer (the largest disk must move at least once, and before that the other
n−1 must all sit on the spare peg).

## 6. Practice

1. CSES *Tower of Hanoi*, *Chessboard and Queens*. Re-solve *Permutations* (Day 3) using
   recursion instead of a formula, for small n, and check it against your formula.
2. Read JE ch. 1–2 ([Erickson](https://jeffe.cs.illinois.edu/teaching/algorithms/)) and
   UG [Complete Search with Recursion](https://usaco.guide/bronze/complete-rec).

**Checkpoint:** you can write the choose/explore/un-choose template from memory, and
prove the Tower of Hanoi move count.
