# Day 1: Setup, first programs, input/output

**Goal:** by the end of today you can write a C++ program, run it, and get it accepted by an
online judge.
**Math bridge:** a program is a constructive proof with *every* step written out. The
computer is a referee who checks nothing except whether you followed your own steps exactly.

---

## 1. How contest programming works

A contest problem gives you a statement, an **input format**, an **output format** and
**constraints** (e.g. `1 ≤ n ≤ 10⁶`). You submit source code. The judge compiles it, runs it on
hidden test files fed to *standard input*, and compares what you print to *standard output*.

| Verdict | Meaning | Usual cause |
|---------|---------|-------------|
| AC (Accepted) | Correct on every test | 🎉 |
| WA (Wrong Answer) | Ran, printed the wrong thing | Logic bug, overflow, wrong format |
| TLE (Time Limit Exceeded) | Too slow (usually limit 1 s) | Algorithm too slow for the constraints |
| RE (Runtime Error) | Crashed | Array index out of range, division by zero, deep recursion |
| CE (Compile Error) | Did not compile | Syntax error |

Never print prompts like `"Enter n:"`. The judge reads your output literally.

## 2. Get a working setup (pick one)

1. **Zero install (start here):** open the [USACO Guide IDE](https://ide.usaco.guide/), choose
   C++, paste code, press Run. Also read UG
   [Running Code Online](https://usaco.guide/general/running-code-online).
2. **Local (do this by Day 3).** Follow the step-by-step
   [setup guide for macOS and Windows](../docs/setup.md). It ends with running
   `make test` in this repository; when that prints `0 failing case(s)`, you are ready.

Compile and run from a terminal (inside this repo):

```sh
g++ $(tools/cxxflags.sh) day1.cpp -o day1     # compile
./day1                                        # run, then type the input
./day1 < input.txt                            # or feed input from a file
```

> **macOS note.** Apple's compiler has no `<bits/stdc++.h>`. `tools/cxxflags.sh` adds
> this repo's fallback copy (and repairs a common broken-install problem), so always
> compile through it. The judges use GCC, where the header exists.

## 3. Anatomy of a program

```cpp
#include <bits/stdc++.h>   // pull in the whole standard library
using namespace std;       // write cout instead of std::cout
using ll = long long;      // short name for 64-bit integers

int main() {               // execution starts here
    ll a, b;               // declare two variables
    cin >> a >> b;         // read them from input (any whitespace separates)
    cout << a + b << "\n"; // print their sum, then a newline
    return 0;              // 0 = "finished normally"
}
```

Every statement ends with `;`. Blocks are wrapped in `{ }`. Lines starting with `//` are
comments. Copy `templates/template.cpp` for each new problem.

## 4. Variables and types

A **variable** is a named box holding a value of a fixed **type**:

| Type | Holds | Range |
|------|-------|-------|
| `int` | integers | about ±2.1 × 10⁹ (2³¹ − 1) |
| `long long` (`ll`) | integers | about ±9.2 × 10¹⁸ (2⁶³ − 1) |
| `double` | real numbers (≈15 significant digits) | approximate. Never compare with `==` |
| `char` | one character | `'A'`, `'7'`, … |
| `string` | text | `"hello"` |
| `bool` | `true` / `false` | |

`x = x + 3;` is **not an equation**: it means "compute x + 3, then store the result in x".
Shorthand: `x += 3;`, `x++;`.

**Overflow:** when an `int` exceeds 2³¹ − 1 it silently wraps to a negative number. The
compiler doesn't warn and the judge just says WA. Rule of thumb: **if a value can exceed
2 · 10⁹, use `long long`**. Products of two `int`s are a classic trap:

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int a = 100000, b = 100000;
    long long wrong = a * b;           // int * int overflows BEFORE conversion
    long long right = 1LL * a * b;     // promote first, then multiply
    cout << wrong << " " << right << "\n";
}
```

## 5. Worked problem: CSES *Weird Algorithm*

> Start from n. If n is even, halve it; if odd, replace it with 3n + 1. Print every value
> until you reach 1. Constraint: 1 ≤ n ≤ 10⁶.

Think first: will `int` do? Starting from n ≤ 10⁶, the sequence can climb past 2³¹ (it does
for some inputs below 10⁶). That is the trap, so use `long long`.

New tools: the **`while` loop** repeats its body as long as the condition is true. The
**ternary** `cond ? x : y` evaluates to `x` if `cond` holds, else `y`. `n % 2` is the remainder
mod 2.

Write it yourself first. Reference: `solutions/cses/weird-algorithm/sol.cpp`.

## 6. Common Day-1 bugs

- Forgetting `;` or a closing `}` (read the **first** compiler error. Later ones are often
  knock-on effects).
- Printing extra text, or forgetting spaces/newlines between numbers.
- `int` where `long long` was needed.
- Using `=` (assignment) where you meant `==` (comparison).

## 7. Practice (in order)

1. ORAC *Starter Set I* (from [orac2.info/learn](https://orac2.info/learn/)).
2. CSES *Weird Algorithm*. Submit until you get AC.
3. Read [learncpp: cout, cin and endl](https://www.learncpp.com/cpp-tutorial/introduction-to-iostream-cout-cin-and-endl/).
4. Watch [CS50x Week 0](https://cs50.harvard.edu/x/weeks/0/) if "algorithm" still feels abstract.

**Checkpoint:** explain, with a concrete number, why `int` fails and `long long` works for
*Weird Algorithm*.
