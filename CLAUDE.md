# CLAUDE.md — IOI / AIO Training Course

This folder holds a curriculum for **high-school students who are strong at olympiad
mathematics but have never programmed**, preparing them for the **AIO** (Australian
Informatics Olympiad) and, longer term, the **IOI** (International Olympiad in Informatics).

## Target learner (design every artefact for this person)

- Math level: comfortable with IMO problems 1/4 and working on 2/5 — i.e. solid
  combinatorics, graph theory, induction, invariants, extremal arguments, pigeonhole,
  double counting, and rigorous proof writing.
- Computing level: **zero**. Has never used a terminal, compiler or text editor for code.
  Does not know what a variable, loop, array or function is.
- Implication: the *ideas* in algorithms will feel easy and fast; the *implementation*
  (syntax, off-by-one errors, debugging, reading input, overflow) is the real bottleneck.
  Material must spend its time on the second, not over-explain the first.

## Pedagogical principles

1. **Math bridge first.** Introduce every algorithm by mapping it to math the student
   already knows (induction ↔ recursion/DP correctness, invariant ↔ loop invariant,
   exchange argument ↔ greedy proof, double counting ↔ complexity analysis,
   handshake lemma ↔ adjacency lists, etc.). Keep a "Math bridge" line in each lesson.
2. **Code every day.** No day is reading-only. Each lesson ends with problems submitted
   to an online judge (CSES, ORAC, AtCoder, oj.uz) so correctness is verified by a machine.
3. **Prove, then implement, then stress-test.** Students write a one-paragraph
   correctness/complexity argument before coding, and learn to compare a fast solution
   against a brute-force one on random inputs.
4. **Subtask thinking.** AIO and IOI award partial credit per subtask. Teach students to
   bank easy subtasks (brute force) before chasing the full solution.
5. **Constraints → complexity.** Always read `N` first: ~10⁸ simple operations/second is
   the working budget (N ≤ 20 → 2ᴺ, N ≤ 5000 → N², N ≤ 2·10⁵ → N log N).

## Language and tooling conventions

- **Language: C++17** (with `#include <bits/stdc++.h>`, `using namespace std;`,
  `long long` by default for sums). C++ is the standard IOI language; AIO also
  accepts others, but we teach one language only.
- Students may start in an online IDE (see USACO Guide "Running Code Online") and
  move to a local setup (VS Code + g++) in week 1.
- Code samples in this repo: short, competitive style, compile with
  `g++ -std=c++17 -O2 -Wall -Wextra -fsanitize=address,undefined`.

## Canonical resources (prefer these; all links were verified on 2026-10-18)

| Kind | Resource | URL |
|------|----------|-----|
| Core textbook (free) | *Competitive Programmer's Handbook* — A. Laaksonen ("CPH") | https://cses.fi/book/book.pdf |
| Problem set paired with CPH | CSES Problem Set | https://cses.fi/problemset/ |
| Structured online course + embedded videos | USACO Guide | https://usaco.guide/ |
| Algorithm reference | cp-algorithms | https://cp-algorithms.com/ |
| Proof-oriented textbook (great fit for math students) | *Algorithms* — Jeff Erickson (free) | https://jeffe.cs.illinois.edu/teaching/algorithms/ |
| C++ language tutorial | learncpp.com | https://www.learncpp.com/ |
| C++ reference | cppreference | https://en.cppreference.com/w/ |
| Absolute-beginner video intro | Harvard CS50x | https://cs50.harvard.edu/x/ |
| University lecture videos | MIT 6.006 (Spring 2020) | https://ocw.mit.edu/courses/6-006-introduction-to-algorithms-spring-2020/video_galleries/lecture-videos/ |
| Algorithm animations | VisuAlgo | https://visualgo.net/en |
| Video channels | Errichto, Colin Galen, Abdul Bari | https://www.youtube.com/@Errichto · https://www.youtube.com/@ColinGalen · https://www.youtube.com/@abdul_bari |
| AIO training site + past papers | ORAC (official AIO trainer) | https://orac2.info/learn/ · https://orac2.info/hub/aio/ |
| AIO organiser | Australian Maths Trust | https://www.amt.edu.au/ |
| IOI official + syllabus | ioinformatics.org | https://ioinformatics.org/page/syllabus/12 |
| IOI past problems (judge) | oj.uz | https://oj.uz/problems/source/22 |
| DP practice | AtCoder Educational DP Contest | https://atcoder.jp/contests/dp |
| Paid book (optional) | *Competitive Programming 4* — Halim | https://cpbook.net/ |

CPH chapter numbers used throughout: 1 Intro · 2 Time complexity · 3 Sorting ·
4 Data structures · 5 Complete search · 6 Greedy · 7 DP · 8 Amortized analysis ·
9 Range queries · 10 Bit manipulation · 11 Basics of graphs · 12 Graph traversal ·
13 Shortest paths · 14 Tree algorithms · 15 Spanning trees · 16 Directed graphs ·
17 Strong connectivity · 18 Tree queries · 19 Paths and circuits · 20 Flows and cuts ·
21 Number theory · 22 Combinatorics · 23 Matrices · 24 Probability · 25 Game theory ·
26 String algorithms · 27 Square root algorithms · 28 Segment trees revisited ·
29 Geometry · 30 Sweep line.

## Repository layout

```
CLAUDE.md                   ← this file: audience, principles, conventions, resources
README.md                   ← GitHub landing page
docs/setup.md               ← student setup guide: compiler, VS Code, Python, Git (macOS/Windows)
plan/30-day-plan.md         ← day-by-day bootcamp (zero → AIO-ready, IOI on-ramp)
plan/after-30-days.md       ← months 2–12 roadmap toward IOI
lessons/dayNN-<topic>.md    ← expanded lesson notes (all 30 days written)
lessons/{a,b,c}NN-<topic>.md ← months 2–12 lesson notes, one per topic (Phases A, B, C)
solutions/<judge>/<name>/   ← sol.cpp + N.in/N.out tests (+ check.py if many answers valid)
templates/                  ← template.cpp, bits/stdc++.h fallback, stress/ tool + example,
                               grader/ (IOI function-style task: header, grader, stub, tests),
                               interactive/ (local interactor runner + CSES Hidden Integer)
tools/                      ← cxxflags.sh, run_tests.py, check_links.sh, tests/
Makefile                    ← make test | lint | links | stress
.github/workflows/ci.yml    ← runs make lint + make test on GCC
```

The 30-day course and the month 2–12 lesson notes (Phases A–C of
`plan/after-30-days.md`) are complete.

## Tooling conventions

- Always compile through `tools/cxxflags.sh` (adds the `bits/stdc++.h` fallback and fixes
  macOS Command Line Tools installs whose clang cannot find libc++ headers).
- Every reference solution gets tests. Expected outputs must come from an **independent**
  source (the judge's sample or a Python brute force), never from running `sol.cpp`.
  Multi-answer problems get a `check.py`, verified to reject wrong outputs.
- Every complete program (a ```cpp block containing `main`) in `lessons/` must compile.
  `tools/tests/test_lessons.py` enforces this.
- Run `make lint && make test` before every commit, and `make links` after adding URLs.

## Rules for editing this course

- **Verify every external link** before adding it (`curl -s -o /dev/null -w '%{http_code}' URL`;
  note USACO Guide returns 404 for missing pages, Codeforces/AMT may return 403 to curl
  — check those in a browser). Prefer stable section/chapter pages over individual
  YouTube video IDs, which rot.
- Cite problems by **judge + exact name** (e.g. CSES "Dice Combinations") so they can be
  found even if URLs change.
- Do not state contest dates/rules as fact without checking AMT / ioinformatics.org for
  the current year; say "check the current year's rules" otherwise.
- Keep each day's entry in the same template: Goal · Math bridge · Read · Watch ·
  Practice · Checkpoint.
- Keep files under ~800 lines; split into `lessons/` when a day grows.
