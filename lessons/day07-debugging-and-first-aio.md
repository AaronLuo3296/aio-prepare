# Day 7: Debugging, stress testing, first AIO problems

**Goal:** find bugs *systematically* instead of staring at code, then meet real AIO problems.
**Math bridge:** a stress test is a search for a counterexample. If your fast solution and
an obviously-correct brute force ever disagree, the smallest disagreeing input is your
counterexample, and it is usually tiny.

---

## 1. Let the tools find bugs for you

Compile with warnings and sanitizers while developing:

```sh
g++ $(tools/cxxflags.sh) -fsanitize=address,undefined sol.cpp -o sol
```

- `-Wall -Wextra` (included by `tools/cxxflags.sh`) warns about unused variables,
  signed/unsigned comparisons, missing returns… **Read every warning.**
- `-fsanitize=address` reports out-of-bounds array access *at the exact line*.
- `-fsanitize=undefined` reports signed integer overflow, division by zero, and more.

Print-debugging: write to `cerr`, not `cout`. Judges ignore `cerr`, so a forgotten debug
line won't cause WA.

```cpp
cerr << "i=" << i << " sum=" << sum << "\n";
```

See UG [Basic Debugging](https://usaco.guide/general/basic-debugging).

## 2. Stress testing

You need three files:

1. `sol.cpp`: your fast solution.
2. `brute.cpp`: a slow, *obviously correct* solution (e.g. try everything).
3. `gen.py`: prints one random **small** input, seeded by its argument.

Then let the repo's script compare them on hundreds of inputs:

```sh
templates/stress/stress.sh sol.cpp brute.cpp gen.py 500
```

**Try the built-in example now.** It contains a classic bug:

```sh
templates/stress/stress.sh templates/stress/buggy_max_subarray.cpp \
    templates/stress/brute_max_subarray.cpp templates/stress/gen_max_subarray.py
```

It reports a mismatch within a few iterations on an input like `n = 1, a = [-8]`.
Open `buggy_max_subarray.cpp`, find why (hint: what is the answer when every number is
negative?), fix it, and rerun until you see `OK: 500 random tests agree`.

Keep generated inputs **small** (n ≤ 8, values in [−10, 10]). Small counterexamples are
easy to trace by hand.

## 3. The error log

Keep a file `error-log.md`. Every WA/TLE/RE gets one row:

| Date | Problem | Verdict | Root cause | Category | Lesson |
|------|---------|---------|------------|----------|--------|
| D2 | Increasing Array | WA | sum stored in `int` | overflow | sums of many values → `long long` |
| D5 | Apple Division | WA | `1 << n` loop used `<=` | off-by-one | masks are 0 … 2ⁿ − 1 |

Categories to use: overflow, off-by-one, misread statement, wrong algorithm, TLE (bad
complexity), uninitialised variable, output format. Review the counts every week. They
tell you what to drill.

## 4. How to approach an AIO paper

AIO papers have several problems in increasing difficulty, each split into **subtasks**
worth partial marks (check the current year's rules for exact format and timing). Strategy:

1. **Read every problem first** (≈10 minutes). Note the subtask constraints.
2. **Bank the easy points:** for each problem, a brute force that solves the smallest
   subtask is often 10 minutes of work for 20–40% of its marks.
3. Then go for full solutions, easiest first. Use the constraints table (Day 4) to guess the
   intended complexity.
4. Before submitting, test on the samples **and** an edge case (n = 1, all equal, maximum
   values).
5. Never sit stuck for 30+ minutes on one problem while easier subtasks elsewhere are unclaimed.

## 5. Practice

1. Run the stress-test example above and fix the bug.
2. From [ORAC AIO Sets](https://orac2.info/hub/aio/): take **the first two problems** from
   2–3 different years. Score every subtask you can.
3. Start your `error-log.md` with every bug from Week 1.
4. Read UG [Contest Strategy](https://usaco.guide/general/contest-strategy).

**Checkpoint:** an error log with at least 10 entries, and you can name your most common
bug category. Run `make test` in this repo and see all Week 1 reference solutions pass.
