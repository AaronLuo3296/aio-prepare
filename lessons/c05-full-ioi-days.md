# Phase C.5: Full IOI days and beyond Platinum

*Months 7–12, [roadmap](../plan/after-30-days.md#phase-c-months-712-ioi-toolkit-part-2-and-full-past-papers).
From month 7 onwards, one full past IOI day every one or two weeks, alongside the topic
lessons C.1–C.4.*

**Goal:** turn knowledge into points on 5-hour, 3-task IOI days. Know within 30 minutes
which subtasks are "free", and spend the remaining time where the expected score per
minute is highest.
**Math bridge:** a contest is an allocation problem. Each subtask has a value and an
uncertain cost in time. Partial credit makes the greedy "cheapest points first" close to
optimal, the same greedy-by-ratio idea as fractional knapsack (Day 9).

---

## 1. Setting up a virtual IOI day

- Choose a past IOI day on [oj.uz](https://oj.uz/problems/source/22) that you have not
  read. oj.uz also archives other olympiads (APIO, BOI, CEOI, JOI and many national
  ones) on its [source list](https://oj.uz/problems/source), which gives far more
  full-length papers than the IOI alone.
- 5 hours, 3 tasks, no editorials, no internet except the judge and
  [cppreference](https://en.cppreference.com/w/). Use the provided graders locally
  (`templates/grader/`, `templates/interactive/`).
- Check the current IOI rules (task count, duration, feedback) on
  [ioinformatics.org](https://ioinformatics.org/) and simulate the current format.

## 2. The first 30 minutes

1. Read all three tasks fully, including every subtask and its constraints.
2. For each subtask, write down: the intended complexity (from N), the idea if it is
   obvious, and an estimate in minutes.
3. Mark the "free" subtasks: brute force, n ≤ 10, a special structure (a path, a star,
   all values equal). On a typical IOI day these are worth a meaningful share of the
   points and take minutes each.
4. Plan the order: free subtasks on **all three** tasks first, then the best
   value-per-minute subtask that remains.

## 3. During the contest

- Keep every accepted version. Write the faster solution as a separate function or file,
  and dispatch by subtask (`if (n <= 5000) slow(); else fast();`) so you never lose
  points you already banked.
- Stress-test the fast solution against the slow one before submitting it for the large
  subtasks. Both are already written, so this costs a few minutes.
- If an idea has not progressed in 45 minutes, switch tasks and come back later.
- In the last 30 minutes do no new ideas. Make sure every task has its best version
  submitted.

## 4. After the contest

Score it, then upsolve within a week: read the official solution for one subtask beyond
what you got, then implement it without looking. Log the result:

| Task | Score | Free points missed? | Next subtask: idea known? | Next subtask: implemented? |
|------|-------|---------------------|---------------------------|----------------------------|

"Free points missed" should be empty after the first few papers. If it is not, the
problem is the routine in section 2, not knowledge.

## 5. Beyond Platinum

Once C.1–C.4 are comfortable, UG [Advanced](https://usaco.guide/adv/) covers the rest of
what shows up in hard IOI tasks: link-cut trees, offline dynamic connectivity, slope
trick, persistent structures, string suffix structures, FFT. Learn them **when a past
paper needs them**, not in syllabus order. At this stage the upsolving list from your
virtual contests is the best guide to what to study next.

**Checkpoint (end of Phase C):** consistent partial scores on recent IOI days, and an
empty "free points missed" column for the last three papers.
