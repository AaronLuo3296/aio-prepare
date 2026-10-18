# Day 9: Greedy algorithms and exchange arguments

**Goal:** recognise greedy structure, and **prove** a greedy rule before coding it.
**Math bridge:** the exchange argument. Take any optimal solution, swap one choice for the
greedy one, and show the result is still optimal. You have done this in olympiad
combinatorics many times. Greedy without a proof is guessing, and plausible greedy rules
are wrong surprisingly often.

---

## 1. The pattern

1. Guess a rule ("always take the X-est remaining item").
2. Try to break it on tiny cases (paper, or a stress test against brute force: Day 7).
3. Prove it with an exchange argument.
4. Code it. It is usually "sort, then one loop".

## 2. Worked problem: CSES *Movie Festival*

> n movies with start and end times. Watch as many complete movies as possible.

Candidate rules: shortest movie first? Earliest start? Earliest **end**? The first two fail
(find counterexamples with 3 movies). The third is right.

**Claim.** Some optimal schedule starts with the movie m₁ that ends earliest.
**Proof.** Take an optimal schedule and let f be its first movie. Replace f by m₁. Since m₁
ends no later than f, m₁ still finishes before the second movie starts, so the schedule is
valid and has the same size. Now apply induction to the movies starting after m₁ ends. ∎

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> movies(n);        // stored as (end, start) so sort orders by end
    for (auto& [b, a] : movies) cin >> a >> b;
    sort(movies.begin(), movies.end());

    int watched = 0, freeAt = 0;
    for (auto [b, a] : movies) {
        if (a >= freeAt) {                   // starts after (or as) the last one ends
            watched++;
            freeAt = b;
        }
    }
    cout << watched << "\n";
}
```

## 3. Sweep line: CSES *Restaurant Customers*

"Maximum number of intervals overlapping at one moment." Turn each customer into two
**events**, (arrival, +1) and (departure, −1). Sort events by time and keep a running total.
The answer is the largest running total. This "sort the events, then sweep" idea returns in
Week 4 (CPH ch. 30).

## 4. Two classic optimality facts

- **Median minimises Σ|xᵢ − c|** (CSES *Stick Lengths*). Moving c one step to the right
  changes the sum by (#points left of c) − (#points right of c), so the sum decreases
  until c reaches the median. Write this up properly; it is a two-line proof.
- **Shortest job first** (CSES *Tasks and Deadlines*). The reward is Σ dᵢ − Σ fᵢ, and the
  deadlines are fixed, so only Σ fᵢ (sum of finishing times) matters. If a longer task
  directly precedes a shorter one, swapping them lowers Σ fᵢ. So the sorted order is
  optimal. Notice that the deadlines turned out to be a red herring.

Both answers can reach about 2·10⁵ · 10⁹, so use `long long`.

## 5. When greedy fails

Coins {1, 3, 4} and target 6: "largest coin first" gives 4+1+1 (3 coins) but 3+3 uses 2.
When no exchange argument works, you usually need DP (Day 12).

## 6. Practice

1. CSES *Movie Festival*, *Restaurant Customers*, *Stick Lengths*, *Tasks and Deadlines*.
2. Read CPH ch. 6, JE ch. 4, UG [Intro to Greedy](https://usaco.guide/bronze/intro-greedy)
   and [Greedy with Sorting](https://usaco.guide/silver/greedy-sorting).

Reference solutions: `solutions/cses/` (`movie-festival`, `restaurant-customers`,
`stick-lengths`, `tasks-and-deadlines`).

**Checkpoint:** a written exchange-argument proof for *Movie Festival*, and a 3-movie
counterexample for "shortest movie first".
