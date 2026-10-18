# Day 27: Mock contest #3 (full AIO simulation)

**Goal:** the most realistic rehearsal yet: the most recent AIO paper you have not seen,
in one sitting, under strict exam conditions.
**Math bridge:** a competition rewards a well-practised routine as much as raw ability.
Today tests the routine.

---

## 1. Setup

- Pick the **most recent unseen** Senior paper from [ORAC AIO Sets](https://orac2.info/hub/aio/).
  Check the current year's rules on the [AMT site](https://www.amt.edu.au/) for the real
  duration and allowed materials; use 3 hours if unsure.
- No internet besides the judge and cppreference. Phone in another room. One sitting.
- Use the time plan from [Day 14](day14-mock-contest-1.md) and the graph checklist from
  [Day 21](day21-mock-contest-2.md).

## 2. Week 4 checklist

- [ ] Range query with updates? Fenwick for sums, segment tree for min/max. Use 1-indexed
      Fenwick positions.
- [ ] Modulus: every `+` and `*` reduced, products in `long long`, subtraction followed by
      `+ MOD`.
- [ ] N ≤ 20: consider a bitmask. Is a 2ᴺ·N² table global, and does it fit in memory?
- [ ] Tree with many queries: binary lifting / Euler tour instead of a walk per query.
- [ ] Before submitting: does the output format match the statement exactly?

## 3. After the contest

1. Record the per-subtask score next to mocks #1 and #2 in the plan's progress tracker.
2. Upsolve everything, with the official solutions where they exist.
3. For each lost subtask, tag the cause in your error log: *idea*, *implementation*,
   *time management* or *reading*. Day 28 works from these tags.

**Checkpoint:** the paper upsolved, and a tagged error-log entry for every subtask you
missed.
