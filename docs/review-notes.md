# Maintainer review notes: months 2–12 (Phases A–C)

What to check by hand in commits `9f4395d`, `b09610b`, `d63e5d0` and `e1ff560`. CI
(`make lint && make test`) passes. It proves that every program compiles, every reference
solution matches its tests and each `check.py` rejects wrong output. It cannot prove the
items below. Tick them off and delete this file when done.

## 1. Mathematics in the lessons (highest value)

The audience reads proofs closely. A wrong argument costs more trust than a missing one.

- [ ] Every **Math bridge** line states something true and actually used later in the lesson.
- [ ] Correctness sketches: exchange argument for multiset greedy (A.1), rerooting
      formula (A.2), Bellman–Ford "n−1 rounds" and the negative-cycle reachability caveat
      (A.3), Kosaraju order argument and 2-SAT "x and ¬x in one SCC" (B.2),
      Sprague–Grundy theorem statement (B.5), HLD O(log n) light edges and centroid depth
      (C.1), max-flow = min-cut and König (C.2), CHT monotonicity and D&C
      opt-monotonicity conditions (C.3), cross-product orientation (C.4).
- [ ] Complexity claims, especially Mo's block size derivation (B.4) and the
      O(log² n) HLD path query (C.1).

## 2. Contest facts (must not be stated as fixed)

- [ ] A.4 (checkpoint paper) and C.5 (full IOI days): durations, subtask scoring and the
      AIO → AIIO → team-selection pathway. These should say "check the current year's
      rules" wherever they give a number. Compare against AMT and ioinformatics.org.

## 3. Problem citations

`make links` checks URLs, but most problems are cited by **judge + name** without a URL.

- [ ] Each cited name exists on its judge exactly as spelled. Spot-check the less common
      ones: CSES *Monster Game I/II*, *Subarray Squares*, *Fixed-Length Paths I*,
      *Point Location Test*, *Hotel Queries*, *Salary Queries*, *Coin Collector*,
      *Distinct Routes*, *Grundy's Game*.
- [ ] Each lesson's practice list goes from easy to hard, and the "reference solution
      below" problems are the ones in `solutions/README.md`.

## 4. Reference solutions (spoilers: 35 new, 118 total)

- [ ] Style is suitable for a beginner to read: short, commented where it matters, no
      clever macros.
- [ ] `__int128` use (frog-3, monster-game-i, polygon-area) is explained in its lesson.
      Consider whether `long long` with a proof of no overflow would teach more.
- [ ] Checkers: convex-hull, cycle-finding, finding-a-centroid, flight-routes-check,
      giant-pizza, planets-and-kingdoms, police-chase, school-dance. Each one should test
      the *property* (valid cut, valid matching, …), not just the format.
- [ ] Timing was measured with GCC in Docker, not on the Mac (Apple libc++ `cin` is far
      slower). Optional: submit a few to CSES to confirm.

## 5. Interactive kit (`templates/interactive/`)

- [ ] `README.md` is followable by a student who has only used `make test`.
- [ ] `interact.py` cleanly kills both processes on a timeout or a wrong answer.

## 6. Known gaps (deliberate or to-do)

- **No "Watch" line** in lessons `a01`–`c05`. The day entries in `plan/30-day-plan.md` each
  have one, so phase students get no video pointers. Optional: add verified channel or
  playlist pages, not single video IDs, which rot.
- B.4 has one reference solution. The other lessons have about three each.
- B.6 and C.5 have no solutions by design (interactive and full-paper practice).
