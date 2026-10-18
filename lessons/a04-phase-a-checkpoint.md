# Phase A.4: Checkpoint: a full AIO Senior paper

*End of month 3, [roadmap](../plan/after-30-days.md#phase-a-months-23-finish-the-core).*

**Goal:** prove that Phase A worked: near-full marks on a recent, unseen AIO Senior
paper under exam conditions. Then decide whether to start Phase B or spend more time on
the core.
**Math bridge:** a checkpoint is a test of the hypothesis "the core is done". Decide the
pass criterion **before** you sit the paper, so the result cannot be argued away.

---

## 1. Before the paper

- Choose the most recent Senior paper you have **not** seen on
  [ORAC AIO Sets](https://orac2.info/hub/aio/). Keep one or two unseen papers in reserve
  for retakes.
- Check the current year's format (number of problems, duration, subtasks) on the
  [Australian Maths Trust](https://www.amt.edu.au/) site and simulate exactly that.
- Pass criterion (write it down now): for example "every problem attempted, all but the
  last fully solved, and a subtask on the last".

## 2. During the paper

The Day 14/21/27 routine still applies:

1. Read **all** problems first (10 minutes). Note N for each subtask and the complexity
   it allows.
2. Bank the cheapest points first: brute force subtasks on every problem before anyone
   gets your full attention.
3. For each full solution: one paragraph of proof and complexity, then code, then a
   stress test against your brute force if time allows.
4. Stop starting new ideas 15 minutes before the end. Re-read the output formats and
   resubmit your best version of everything.

## 3. After the paper

Mark it honestly with the official tests on ORAC. Then upsolve every problem you did not
get full marks on, within 48 hours. Log each lost point under one of these:

| Lost to | Fix before Phase B |
|---------|--------------------|
| Did not recognise the model | More of the CSES section it belongs to; UG module for it |
| Recognised it, could not finish the proof | Do the proof during upsolving; read the editorial only after 30 min |
| Implementation bug | Stress-test routine; add the bug to your error log |
| Too slow (TLE) | Re-check complexity vs. constraints; fast I/O; avoid `endl` in loops |
| Time management | One extra full paper next week, strictly timed |

## 4. Decision

- **Passed:** start [Phase B](b01-string-algorithms.md). Keep the weekly contest and
  upsolving rhythm from the [roadmap](../plan/after-30-days.md#weekly-rhythm-1012-hweek-alongside-school).
- **Not passed:** spend 2–3 more weeks on the categories that lost the most points, then
  sit one of the reserved papers. Moving on with gaps in the core makes Phase B slower,
  not faster.

**Checkpoint:** the pass criterion is met, and every problem from the paper has been
upsolved and logged.
