# Day 2: Conditionals, loops, integer arithmetic

**Goal:** `if`/`else`, `for`, `while`; integer division and `%`; reasoning about loops.
**Math bridge:** a **loop invariant** is an induction hypothesis. It holds before the loop
(base case), each iteration preserves it (inductive step), and at exit it gives you the answer.

---

## 1. Conditionals

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int score;
    cin >> score;
    if (score >= 90) {
        cout << "gold\n";
    } else if (score >= 60) {
        cout << "silver\n";
    } else {
        cout << "try again\n";
    }
}
```

Comparisons: `==  !=  <  <=  >  >=`. Logic: `&&` (and), `||` (or), `!` (not).
`&&` and `||` **short-circuit**: in `i < n && a[i] > 0` the right side is skipped when `i < n` is false.

## 2. Loops

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    // for (start; condition; step): i = 1, 2, ..., 10
    long long sum = 0;
    for (int i = 1; i <= 10; i++) sum += i;
    cout << sum << "\n";                 // 55

    // while: repeat until the condition fails. Here, the digit sum of n.
    long long n = 9875, digits = 0;
    while (n > 0) {
        digits += n % 10;
        n /= 10;
    }
    cout << digits << "\n";              // 29
}
```

- `break` leaves the loop immediately. `continue` jumps to the next iteration.
- **Read t test cases** with `int t; cin >> t; while (t--) { ... }`.

**Invariant practice.** In the digit-sum loop the invariant is
`digits + (digit sum of n) = digit sum of the original n`. It is true at the start, each
iteration moves one digit from `n` into `digits`, and when `n = 0` the answer is `digits`.
Write such an invariant (one line, as a comment) for every non-trivial loop this week.

## 3. Integer arithmetic: three traps for mathematicians

1. **Division truncates toward zero.** `7 / 2 == 3`, but `-7 / 2 == -3` (not −4).
2. **`%` can be negative.** `-7 % 3 == -1`, not 2. For a mathematical residue use
   `((a % m) + m) % m`.
3. **Ceiling division** for positive integers: `(a + b - 1) / b`.

Use `long long` for any sum of many numbers. Sum of 2·10⁵ values up to 10⁹ is 2·10¹⁴.

## 4. Worked problem: CSES *Missing Number*

> Numbers 1..n with one missing are given (n − 1 of them). Find the missing one.

Math does all the work: answer = n(n+1)/2 − (sum of input). One pass, O(n). With n up to
2·10⁵, n(n+1)/2 ≈ 2·10¹⁰ overflows `int`, so use `long long`. Alternative: XOR all of
1..n and all inputs. Every number present twice cancels.

## 5. Worked problem: CSES *Number Spiral*

> The grid is filled in a snake-like spiral (1 in the corner, layer k contains k²−(k−1)²
> numbers). Answer t queries: the value at row y, column x, with y, x ≤ 10⁹.

You cannot build a 10⁹ × 10⁹ grid. Find a formula instead:

1. Draw the 5 × 5 spiral by hand. Cell (y, x) lies on layer z = max(y, x), and layer z
   contains exactly the values (z−1)² + 1, …, z².
2. The direction alternates with the parity of z. In one parity the layer *ends* at
   (z, 1), in the other it *starts* there.
3. Derive both cases, then **test your formula against the hand-drawn grid** before coding.

Values reach 10¹⁸, so use `long long` (and still not `int` for y, x: y·y overflows).
Reference: `solutions/cses/number-spiral/sol.cpp`.

## 6. Practice

1. ORAC *Starter Set II*.
2. CSES *Missing Number*, *Repetitions*, *Increasing Array*, *Number Spiral*.
3. Watch [CS50x Week 1](https://cs50.harvard.edu/x/weeks/1/) (C syntax is nearly identical here).

**Checkpoint:** *Number Spiral* accepted with an O(1) formula. For *Increasing Array*, state
the loop invariant and the greedy argument for why raising to the running maximum is optimal.
