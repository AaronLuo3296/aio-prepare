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

## Week 2 (CSES Sorting/Searching/DP, AtCoder Educational DP)

| Day | Problems |
|-----|----------|
| 8 | distinct-numbers, apartments, ferris-wheel, concert-tickets |
| 9 | movie-festival, restaurant-customers, stick-lengths, tasks-and-deadlines |
| 10 | static-range-sum-queries, subarray-sums-i, subarray-sums-ii, subarray-divisibility |
| 11 | sum-of-two-values, maximum-subarray-sum, playlist, factory-machines |
| 12 | dice-combinations, minimizing-coins, coin-combinations-i, coin-combinations-ii, removing-digits, atcoder-dp/frog-1, atcoder-dp/frog-2 |
| 13 | grid-paths-dp, book-shop, array-description, edit-distance, atcoder-dp/knapsack-1, atcoder-dp/lcs |

## Week 3 (CSES Graph Algorithms and Tree Algorithms, AtCoder Educational DP)

| Day | Problems |
|-----|----------|
| 15 | counting-rooms, building-roads, message-route, labyrinth |
| 16 | building-teams, round-trip, monsters |
| 17 | shortest-routes-i, shortest-routes-ii, flight-discount |
| 18 | road-reparation, road-construction |
| 19 | course-schedule, longest-flight-route, game-routes, atcoder-dp/longest-path |
| 20 | subordinates, tree-diameter, tree-distances-i, tree-matching, atcoder-dp/independent-set |
