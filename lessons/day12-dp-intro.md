# Day 12: Dynamic programming I

**Goal:** design a DP as **state, transition, base case, evaluation order**, and implement
it bottom-up.
**Math bridge:** DP is a recurrence plus induction. You have solved "in how many ways…"
problems by conditioning on the last step for years. DP is that, with the computer filling
in the table.

---

## 1. The recipe

1. **State:** what does `dp[s]` mean, in one precise sentence? ("the number of ordered
   ways to reach sum s"). Most DP bugs are a vague state.
2. **Transition:** condition on the last decision. That gives a recurrence.
3. **Base case:** usually the empty thing (`dp[0] = 1` ways, or cost 0).
4. **Order:** compute each state after everything it depends on.
5. **Answer:** which state, and the complexity = #states × cost per transition.

## 2. Worked problem: CSES *Dice Combinations*

> Number of ways to get sum n by throwing a die one or more times (order matters), mod 10⁹+7.

State: ways[s]. Last throw d ∈ {1..6}: ways[s] = ways[s−1] + … + ways[s−6], ways[0] = 1.

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;

int main() {
    int n = 3;
    vector<int> ways(n + 1, 0);
    ways[0] = 1;
    for (int s = 1; s <= n; s++)
        for (int d = 1; d <= 6 && d <= s; d++)
            ways[s] = (ways[s] + ways[s - d]) % MOD;
    cout << ways[n] << "\n";                 // 4: 1+1+1, 1+2, 2+1, 3
}
```

Reduce mod **after every addition**. Two values below 10⁹+7 sum to below 2³¹, so `int`
is safe for a single addition, but never for a product (use `long long`).

## 3. Memoisation vs tabulation

The same recurrence can be written top-down: a recursive function with a cache
(`memo[s]`, computed on first call). It is closer to the math, but recursion depth can hit
10⁶ and crash. Bottom-up loops (above) are the default in contests.

## 4. Optimisation instead of counting

CSES *Minimizing Coins*: best[s] = 1 + min over coins c ≤ s of best[s − c], best[0] = 0,
unreachable = ∞. Same shape, `min` instead of `+`. Remember that greedy failed on this
problem (Day 9).

AtCoder DP *Frog 1/2*: cost[i] = min over the last jump length j of cost[i−j] + |hᵢ − h_{i−j}|.

## 5. Ordered vs unordered: *Coin Combinations I* and *II*

Coins {2, 3, 5}, target 9. *I* counts sequences (2+2+5 ≠ 5+2+2): 8. *II* counts multisets: 3.

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> c = {2, 3, 5};
    int x = 9;
    vector<long long> ordered(x + 1, 0), unordered(x + 1, 0);
    ordered[0] = unordered[0] = 1;
    for (int s = 1; s <= x; s++)              // sums outside: condition on the LAST coin
        for (int v : c)
            if (v <= s) ordered[s] += ordered[s - v];
    for (int v : c)                           // coins outside: decide coin types in order
        for (int s = v; s <= x; s++) unordered[s] += unordered[s - v];
    cout << ordered[x] << " " << unordered[x] << "\n";   // 8 3
}
```

The bijection behind the second loop: a multiset is the same as a **non-decreasing**
sequence. Processing coin types in a fixed order counts exactly those. After the outer loop
has handled coins c₁…cᵢ, `unordered[s]` = number of multisets of {c₁…cᵢ} with sum s
(induction on i).

## 6. Practice

1. CSES *Dice Combinations*, *Minimizing Coins*, *Coin Combinations I*,
   *Coin Combinations II*, *Removing Digits*.
2. AtCoder [Educational DP Contest](https://atcoder.jp/contests/dp) *A: Frog 1*, *B: Frog 2*.
3. Read CPH ch. 7, JE ch. 3 and UG [Intro to DP](https://usaco.guide/gold/intro-dp).
   Watch 6.006 Lectures 15–16.

Reference solutions: `solutions/cses/` (`dice-combinations`, `minimizing-coins`,
`coin-combinations-i`, `coin-combinations-ii`, `removing-digits`) and
`solutions/atcoder-dp/` (`frog-1`, `frog-2`).

**Checkpoint:** explain the Coin Combinations I/II difference as a bijection argument, and
write the state sentence for each DP above.
