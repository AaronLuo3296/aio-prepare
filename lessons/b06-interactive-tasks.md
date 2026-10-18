# Phase B.6: Interactive and function-style tasks

*Months 4–6, [roadmap](../plan/after-30-days.md#phase-b-months-46-ioi-toolkit-part-1). About
one week, then continuously: every IOI paper has tasks in this format.*

**Goal:** solve tasks where the judge answers your questions, test them locally with an
interactor, and plan the query budget as part of the solution. This builds on
[Day 26](day26-ioi-format.md), which introduced the function-style grader.
**Math bridge:** a query limit is an **information-theoretic lower bound** problem. If
each answer is YES/NO and there are N possible secrets, you need at least ⌈log₂ N⌉
queries, because k answers distinguish at most 2ᵏ cases. The adversary argument from
olympiad combinatorics ("the judge answers so as to keep as many candidates alive as
possible") is exactly how interactors for the hardest subtasks behave.

**Read:** the task statements and graders of IOI past problems on
[oj.uz](https://oj.uz/problems/source/22) · `templates/interactive/README.md` and
`templates/grader/README.md` in this repo.

---

## 1. Two formats

| Format | You write | Communication | Seen in |
|--------|-----------|---------------|---------|
| stdin/stdout interactive | a whole program | print a query, **flush**, read the reply | Codeforces, CSES *Interactive Problems* |
| function-style | a function such as `int guess(int n)` | call a provided function, e.g. `ask(y)`, which returns the answer | IOI, oj.uz |

In both formats the judge may be **adaptive**: it does not fix the secret in advance, it
only keeps its answers consistent. Never assume the secret is random.

## 2. Local testing

You cannot pipe a file into an interactive program, because the replies depend on your
questions. `templates/interactive/` has a tiny local judge:

```sh
cd templates/interactive
g++ $(../../tools/cxxflags.sh) hidden_integer.cpp -o hidden_integer
python3 interact.py ./hidden_integer hidden_integer_interactor.py 1000000000
```

`interact.py` connects your program's output to the interactor's input and the other way
round, and prints `ACCEPTED`, `WRONG ANSWER` or `TIMEOUT`. A `TIMEOUT` with a correct
algorithm almost always means a missing flush. Use `endl` or `cout << flush` after each
query, and only then read the reply. Copy `hidden_integer_interactor.py` to write an
interactor for a new task. That takes about 15 lines, and is worth it for any task you
spend more than an hour on.

For function-style tasks, `templates/grader/` shows the IOI layout (header, grader, your
file). The grader in the task attachment plays the role of the interactor.

## 3. Budgeting queries

*Hidden Integer*: x ∈ [1, 10⁹], questions "is y < x?", at most 30. Since 2³⁰ > 10⁹, binary
search fits exactly, with **no** slack. An off-by-one that wastes a single query fails.
Test the extremes 1 and 10⁹, and a power of two. `tools/tests/test_interactive.py` does
this for the reference solution.

General habits:

- Count queries in your code, and `assert(count <= LIMIT)` while testing.
- Subtasks usually allow more queries. Bank a simple strategy with a loose budget first
  (e.g. 2 log n), then optimise the constant.
- Read the scoring formula. IOI tasks often give partial credit that depends on the number
  of queries used, so "slightly over the optimal budget" can still be worth most points.
- Print debug output to `cerr`. Anything on `cout` is read by the judge.

## 4. Practice

1. CSES *Interactive Problems*: *Hidden Integer* (reference in
   `templates/interactive/hidden_integer.cpp`), *Hidden Permutation*, *K-th Highest
   Score*.
2. IOI past function-style tasks on [oj.uz](https://oj.uz/problems/source/22). Good ones
   to start with: IOI 2018 *Combo* (also in Day 26), IOI 2016 *Detecting Molecules*
   (not interactive, but function-style), IOI 2017 *The Big Prize* (interactive, scored
   by the number of queries).
3. For one of them, write your own grader or interactor before you write the solution.

**Checkpoint:** *Hidden Integer* accepted on CSES, and your own interactor for one IOI
interactive task, written and used.
