# AIO / IOI Preparation for Olympiad Mathematicians

A course that takes high-school students who are **strong at olympiad mathematics** (IMO
problems 1/4 to 2/5) but have **never programmed** to the **Australian Informatics Olympiad
(AIO)**, and puts them on the road to the **International Olympiad in Informatics (IOI)**.

The premise: these students already know induction, invariants, extremal arguments and graph
theory. Algorithms will feel familiar fast. Writing correct, fast C++ is the real
bottleneck, so the course spends its time there.

## Start here

1. **Set up your computer:** [C++ setup guide for macOS and Windows](docs/setup.md).
2. Read the [30-day plan](plan/30-day-plan.md).
3. Follow the lesson notes day by day: [Weeks 1–2](lessons/) (days 1–14) are written. Later weeks follow
   the plan directly.
4. After Day 30: [the road to the IOI](plan/after-30-days.md).

## Repository layout

| Path | Contents |
|------|----------|
| `docs/setup.md` | Installing a compiler, VS Code, Python and Git (macOS, Windows) |
| `plan/` | 30-day bootcamp and post-bootcamp roadmap |
| `lessons/` | Expanded notes per day (concepts, worked problem, practice, checkpoint) |
| `solutions/` | Reference C++ solutions with tests (**spoilers**: see [its README](solutions/README.md)) |
| `templates/` | Contest starter `template.cpp`, stress-test tool and a worked example |
| `tools/` | Compiler-flag helper, solution test runner, link checker, self-tests |

## Using the tooling

Requires a C++17 compiler (`g++` or Apple clang), Python 3 and `make`. See the
[setup guide](docs/setup.md). On Windows with MinGW, prefix commands with `SANITIZE=0`.

```sh
make test     # tool self-tests + compile/run every reference solution on its tests
make lint     # syntax checks for the Python and shell tooling
make links    # check every external link (needs network)
make stress SOL=sol.cpp BRUTE=brute.cpp GEN=gen.py   # stress-test your own solution
```

Compile your own code with the repo's flags (this also fixes `<bits/stdc++.h>` on macOS):

```sh
g++ $(tools/cxxflags.sh) mysol.cpp -o mysol && ./mysol < input.txt
```

## Main resources

[Competitive Programmer's Handbook](https://cses.fi/book/book.pdf) ·
[CSES Problem Set](https://cses.fi/problemset/) · [USACO Guide](https://usaco.guide/) ·
[cp-algorithms](https://cp-algorithms.com/) ·
[Erickson, *Algorithms*](https://jeffe.cs.illinois.edu/teaching/algorithms/) ·
[ORAC (AIO training)](https://orac2.info/learn/) · [oj.uz (IOI archive)](https://oj.uz/problems/source/22).
The full annotated list is in [CLAUDE.md](CLAUDE.md#canonical-resources-prefer-these-all-links-were-verified-on-2026-10-18).
