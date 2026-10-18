# Reference solutions

> **Spoiler warning.** Read a solution only after you have an accepted submission or
> have been stuck for 25+ minutes *and* read a hint. Copying code teaches nothing.

Each problem lives in `solutions/<judge>/<problem-name>/`:

| File | Meaning |
|------|---------|
| `sol.cpp` | Reference solution. The header comment states the key idea and complexity. |
| `N.in`, `N.out` | Tests: the judge's sample plus extra cases. Expected outputs come from independent Python brute force, not from `sol.cpp`. |
| `check.py` | Present when many answers are valid (e.g. any permutation). It validates the output instead of comparing it exactly. |

Run all tests with `make test-solutions`, or one problem with
`python3 tools/run_tests.py solutions/cses/two-knights`.

## Week 1 (CSES Introductory Problems)

| Day | Problems |
|-----|----------|
| 1 | weird-algorithm |
| 2 | missing-number, repetitions, increasing-array, number-spiral |
| 3 | permutations, palindrome-reorder, two-knights, trailing-zeros |
| 4 | bit-strings, coin-piles, two-sets, gray-code |
| 5 | apple-division, creating-strings |
| 6 | tower-of-hanoi, chessboard-and-queens (+ recursive permutations) |
