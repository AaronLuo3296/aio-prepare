# Day 14: Mock contest #1

**Goal:** sit a full AIO paper under real conditions, then learn as much as possible from it.
**Math bridge:** same as olympiad maths. Read every problem first, bank the easy marks,
and go deep on one hard problem rather than shallow on all of them.

---

## 1. Before the contest

- Choose one Intermediate-level year from [ORAC AIO Sets](https://orac2.info/hub/aio/)
  that you have **not** seen. Check the current year's rules on the AMT site for the real
  duration; use 3 hours if unsure.
- Have ready: your `template.cpp`, the stress-test script (Day 7) and your error log.
- No internet except the judge and cppreference.

## 2. During the contest: a time plan

| Time | Do this |
|------|---------|
| 0:00–0:15 | Read **all** problems. For each, write N's bound and the complexity it allows (Day 4 table). |
| 0:15–1:30 | Solve the easiest problem fully. On the others, submit brute force for the small subtasks. |
| 1:30–2:45 | Pick the problem where your idea is closest to a full solution. Prove, code, stress-test. |
| 2:45–3:00 | Stop starting new ideas. Re-check `long long`, array sizes and output format. |

Rules of thumb:

- A brute force that passes subtask 1 is points in the bank and becomes your stress-test
  reference later.
- Stuck for 20 minutes? Write down what you know and switch problems.
- Wrong answer on a hidden test: test n = 1, all-equal values, and the maximum values
  (overflow) before rereading your algorithm.

## 3. After the contest (the important part)

1. Record your score per problem and subtask.
2. Upsolve every problem. Read the official solution on ORAC where available, then code it
   yourself without looking.
3. Add every bug to the error log with its category (off-by-one, overflow, misread
   statement, wrong algorithm, too slow).
4. Map each lost subtask to a Week 2 topic: sorting, greedy, prefix sums, two pointers,
   binary search or DP. Re-do two practice problems on the weakest topic.

**Checkpoint:** score recorded, every problem upsolved, and a list of which topics cost the
most points.
