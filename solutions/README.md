# Reference solutions

> **Spoiler warning.** Read a solution only after you have an accepted submission or
> have been stuck for 25+ minutes *and* read a hint. Copying code teaches nothing.

Each problem lives in `solutions/<judge>/<problem-name>/`:

| File | Meaning |
|------|---------|
| `sol.cpp` | Reference solution. The header comment states the key idea and complexity. |
| `N.in`, `N.out` | Tests: the judge's sample plus extra cases. Expected outputs come from independent Python brute force, not from `sol.cpp`. |
| `check.py` | Present when many answers are valid (e.g. any permutation). It validates the output instead of comparing it exactly. |

> **Portability heads-up.** The solutions avoid GCC-only extensions so they compile on
> Apple clang too. In particular they use `31 - __builtin_clz(x)` instead of `__lg(x)`,
> which clang rejects. Do the same in your own code if you work on a Mac without GCC.

> **Small tests are not the judge.** The tests here are tiny: the judge's samples plus small
> random cases that a Python brute force can check. They show that a solution gives the
> **right answers**. They do not show that it is **fast enough** or fits in **memory** at the
> real limits (N = 2·10⁵, values up to 10⁹), and that is where the judge's hidden tests
> fail most solutions: TLE, MLE, overflow on large sums, stack overflow from deep recursion.
> A solution that passes `make test` can still fail on the judge. Before submitting your
> own code:
> 1. Check the complexity against the constraints (Day 4 table: about 10⁸ simple steps/s).
> 2. Generate one **max-size** input (e.g. a Python script printing N = 2·10⁵ random
>    values, or a path graph for recursion depth) and time it **without** sanitizers:
>    `g++ $(tools/cxxflags.sh) sol.cpp -o sol && time ./sol < big.txt`.
> 3. Submit to the judge. Only "Accepted" on the judge counts.
>
> Every Week 4 solution was timed this way with GCC on max-size inputs (all under 0.3 s).
> On a Mac with Apple clang, `cin` is much slower, so local times there look worse than on
> the judge (see the [setup guide](../docs/setup.md#daily-workflow)).

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

## Week 4 (CSES Range Queries/Tree Algorithms/Mathematics/DP, AtCoder Educational DP)

| Day | Problems |
|-----|----------|
| 22 | static-range-minimum-queries, dynamic-range-sum-queries, dynamic-range-minimum-queries, range-xor-queries |
| 23 | company-queries-i, company-queries-ii, distance-queries, subtree-queries |
| 24 | exponentiation, exponentiation-ii, counting-divisors, common-divisors, binomial-coefficients |
| 25 | hamiltonian-flights, elevator-rides, atcoder-dp/matching |
| 26 | IOI tasks have no reference solutions here; see `templates/grader/` for the function-style format |

## Months 2–12 (Phases A–C)

Lessons `lessons/a01`–`c05`, following [the roadmap](../plan/after-30-days.md). Every
solution below was also timed with GCC on max-size inputs (paths, stars and other worst
cases for the trees): all under 0.2 s.

| Lesson | Problems |
|--------|----------|
| A.1 | nearest-smaller-values, towers, increasing-subsequence |
| A.2 | removal-game, counting-numbers, tree-distances-ii |
| A.3 | high-score, cycle-finding, planets-queries-i |
| B.1 | string-matching, finding-borders, finding-periods |
| B.2 | planets-and-kingdoms, giant-pizza, flight-routes-check |
| B.3 | range-update-queries, range-updates-and-sums, hotel-queries |
| B.4 | distinct-values-queries |
| B.5 | nim-game-i, nim-game-ii, stair-game |
| B.6 | interactive: see `templates/interactive/` (CSES *Hidden Integer* with a local interactor) |
| C.1 | finding-a-centroid, path-queries-ii, fixed-length-paths-i |
| C.2 | download-speed, police-chase, school-dance |
| C.3 | atcoder-dp/frog-3, monster-game-i, subarray-squares |
| C.4 | point-location-test, line-segment-intersection, polygon-area, convex-hull |

Some solutions use `__int128` for intermediate products (convex hull trick, polygon area).
GCC and clang support it on 64-bit systems. MSVC does not, but contest judges use GCC.
