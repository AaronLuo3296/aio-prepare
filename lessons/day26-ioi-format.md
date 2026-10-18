# Day 26: The IOI format

**Goal:** solve tasks in the IOI style: you implement a *function* that a grader calls,
there is no stdin/stdout, some tasks are interactive, and every task is scored per subtask.
**Math bridge:** an IOI task works like a proof with lemmas. The subtasks are special
cases (N small, the tree is a path, all values distinct) that point toward the general
argument. Solve the special cases first and look for the pattern.

---

## 1. What changes from AIO/CSES

| | AIO / CSES | IOI |
|-|------------|-----|
| You write | a whole program with `main` | one or more functions, no `main` |
| Input | read from stdin | arrives as function arguments |
| Output | print to stdout | the function's return value (or calls you make) |
| Scoring | per test case or subtask | per subtask; max over all your submissions (check the current year's rules) |
| Interactive | rare | common: you call a provided function, e.g. `press(s)`, and calls are limited |

## 2. The grader template

`templates/grader/` is a complete small example: an interface header, a sample grader, a
stub to start from, a reference solution and tests. Read its
[README](../templates/grader/README.md), then:

1. Copy the folder. In the copy, replace `meeting.cpp` with `stub.cpp`, and get subtask 1
   (N ≤ 1000) working with a brute force.
2. Compile with `g++ $(tools/cxxflags.sh) grader.cpp meeting.cpp` (adjust paths) and run
   it on `tests/*.in`.
3. Solve the full task. The math bridge: the slope of p ↦ Σ|xᵢ − p| changes sign at the
   median.

A solution file looks like this. There is no `main`, and the signature is copied
exactly from the header:

```cpp
#include "meeting.h"
#include <bits/stdc++.h>
using namespace std;

long long min_total_walk(vector<int> x) {
    sort(x.begin(), x.end());
    long long p = x[x.size() / 2], total = 0;
    for (int xi : x) total += llabs(xi - p);
    return total;
}
```

## 3. Pitfalls specific to the format

- **Globals between calls.** If the grader calls `init` and then `query` many times,
  globals persist, which is useful. If it calls your solver several times on separate
  test cases, stale globals break it, so reset them.
- **Printing.** `cout` in a function-style task may corrupt the grader's output. Debug
  with `cerr` and delete it before submitting.
- **Local testing.** Each task's attachment package (on oj.uz or the IOI site) contains a
  sample grader. Compile it with your file exactly as in step 2.
- **Interactive limits.** If a task allows at most K calls, have your function count its
  calls and `assert` the count stays within K while you test locally.

## 4. Practice

From the [oj.uz IOI archive](https://oj.uz/problems/source/22):

1. IOI 2011 *Rice Hub*: binary search on the answer + prefix sums (this is the Meeting
   point task with a budget).
2. IOI 2016 *Detecting Molecules*: sorting + two pointers.
3. IOI 2018 *Combo*: interactive. Count your `press` calls.

Take every subtask you can, even if the full solution is out of reach. Before writing
code, write down in one line what each subtask's special case allows. Skim the
[IOI syllabus](https://ioinformatics.org/page/syllabus/12) and tick off what you have
covered. Older papers are in the [IOI contests archive](https://ioinformatics.org/page/contests/10).

(There are no reference solutions for these tasks in this repository. oj.uz shows your
score per subtask, which is the feedback you need.)

**Checkpoint:** your own `meeting.cpp`, built from `stub.cpp`, compiles against the grader
and passes every file in `templates/grader/tests/`, and you have a nonzero score on at
least two of the three IOI tasks.
