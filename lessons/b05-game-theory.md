# Phase B.5: Game theory: winning positions and Sprague–Grundy

*Months 4–6, [roadmap](../plan/after-30-days.md#phase-b-months-46-ioi-toolkit-part-1). About
one week. Olympiad mathematicians usually know most of this already. The new part is
computing it.*

**Goal:** classify positions of impartial games by brute force, compute Grundy values,
combine independent games with xor, and spot the pattern that lets you skip the brute
force.
**Math bridge:** you have seen the win/lose induction (a position is winning iff some move
reaches a losing position) and Bouton's nim theorem. The new fact is **Sprague–Grundy**:
every impartial game position is equivalent to a nim heap of size
g(position) = mex{g(next positions)}, and a sum of independent games has Grundy value
equal to the xor of the parts.

**Read:** CPH ch. 25 · CPA [Sprague–Grundy](https://cp-algorithms.com/game_theory/sprague-grundy-nim.html).

---

## 1. Compute first, then prove

The olympiad instinct is to look for the invariant immediately. In a contest, **compute
the table first**. Write the brute force from the definition, print the win/lose (or
Grundy) values for small states, and look at the pattern:

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    // Subtraction game: remove 1, 2 or 3 sticks from one heap. g[x] = mex over moves.
    const int N = 20;
    vector<int> g(N + 1, 0);
    for (int x = 1; x <= N; x++) {
        set<int> seen;
        for (int take = 1; take <= 3 && take <= x; take++) seen.insert(g[x - take]);
        while (seen.count(g[x])) g[x]++;   // mex
    }
    for (int x = 0; x <= N; x++) cout << g[x] << " ";   // 0 1 2 3 0 1 2 3 ...
    cout << "\n";
}
```

The output shows g(x) = x mod 4, which is *Nim Game II*. The proof by induction comes
afterwards. The brute force is also your stress-test reference for the closed form.

## 2. Combining games

- **Nim** (*Nim Game I*): first player wins iff x₁ ⊕ … ⊕ xₙ ≠ 0. Proof: from xor 0 every
  move gives a nonzero xor. From a nonzero xor, take a heap containing the top set bit of
  the xor and reduce it so the xor becomes 0.
- **Sum of games:** if a position splits into independent subgames, its Grundy value is
  the xor of theirs. With Sprague–Grundy, "n heaps of game G" reduces to "compute g for
  one heap", e.g. x mod 4 above.
- **A move that splits a heap** (*Grundy's Game*: split into two unequal heaps): the
  next position's Grundy value is g(a) ⊕ g(b). Compute g by brute force for n up to a few
  thousand and list the n with g(n) = 0. The last one is 1222, and as far as anyone has
  computed (far beyond 10⁶) no later losing position exists. That is not a proof, but it
  is what the problem expects you to discover.

## 3. Reductions to nim

*Stair Game* (staircase nim): balls on odd stairs do not matter. Whenever the opponent
moves balls from an odd stair to an even one, move the same balls one stair further. So
the game is nim on the even stairs. Reductions of this kind are where the mathematician's
eye pays off. Still confirm them against a brute force for small cases: the reference
tests do exactly that.

## 4. Beyond impartial games

- **Partizan or scoring games** (the players have different moves, or maximise a score):
  Sprague–Grundy does not apply. Use minimax DP, as in *Removal Game*
  ([A.2](a02-dp-patterns.md)).
- **Interactive game tasks** ask your program to *play*: you must output winning moves,
  not just the winner. Keep the move that achieves the mex, not only the value.

## 5. Practice

1. CSES *Nim Game I*, *Nim Game II*, *Stair Game* (reference solutions below).
2. CSES *Grundy's Game*, *Another Game*, *Stick Game* (subtraction game with a given move
   set: plain win/lose DP).
3. AtCoder DP *K – Stones* and *L – Deque* if you have not done them yet.

Reference solutions: `solutions/cses/` (`nim-game-i`, `nim-game-ii`, `stair-game`). Their
tests come from a brute-force game search, not from the formulas.

**Checkpoint:** for a new subtraction game, write the Grundy brute force, find the
period, and prove it by induction, in under 30 minutes.
