# Day 3: Arrays, vectors, strings, functions

**Goal:** store many values (`vector`), work with text (`string`), and split code into
**functions**.
**Math bridge:** an array is a finite sequence a₀, a₁, …, aₙ₋₁. A C++ function is a
function in the mathematical sense, except it may also have side effects (printing, changing
its arguments).

---

## 1. `vector`: a resizable array

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);          // n zeros, indices 0..n-1
    for (int i = 0; i < n; i++) cin >> a[i];

    long long best = a[0];
    for (long long x : a) best = max(best, x);   // range-for: x takes each value
    cout << best << "\n";

    vector<int> squares;             // empty
    for (int i = 1; i <= 5; i++) squares.push_back(i * i);
    cout << squares.size() << " " << squares.back() << "\n";   // 5 25
}
```

**Indices start at 0.** A vector of size n has indices 0 … n−1. `a[n]` is *out of bounds*.
The program may crash, or worse, silently read garbage. The sanitizer flags
(`-fsanitize=address,undefined`, which `make test` uses) turn this into a loud error.
Use them when debugging.

2D grid: `vector<vector<int>> g(rows, vector<int>(cols, 0));`, accessed as `g[r][c]`.

## 2. `string`

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;                        // reads one word (stops at whitespace)
    cout << s.size() << " " << s[0] << "\n";

    array<int, 26> cnt{};            // fixed-size array of 26 zeros
    for (char c : s) cnt[c - 'A']++; // 'A'..'Z' -> 0..25, since chars are numbers
    string rev(s.rbegin(), s.rend());
    cout << (s == rev ? "palindrome" : "not palindrome") << "\n";
}
```

`c - 'A'` works because characters are stored as integers with 'A'…'Z' consecutive.
Use `getline(cin, line)` when you need a whole line including spaces.

## 3. Functions

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll gcd_of(ll a, ll b) {              // return type, name, parameters
    return b == 0 ? a : gcd_of(b, a % b);
}

void double_all(vector<ll>& v) {     // & = by reference: changes the caller's vector
    for (ll& x : v) x *= 2;
}

int main() {
    cout << gcd_of(84, 36) << "\n";  // 12
    vector<ll> v = {1, 2, 3};
    double_all(v);
    cout << v[2] << "\n";            // 6
}
```

Without `&`, the function gets a **copy**: changes are lost, and copying a big vector on
every call is slow. Pass large inputs as `const vector<ll>& v` when you only read them.

## 4. Worked problem: CSES *Two Knights* (derive on paper first)

> For k = 1 … n, count the ways to place two identical knights on a k × k board so they do
> not attack each other.

Complementary counting: total pairs C(k², 2) minus attacking pairs. Two knights attack iff
they are opposite corners of a 2 × 3 or 3 × 2 rectangle. There are (k−1)(k−2) rectangles
of each orientation, and each contains exactly 2 attacking pairs. So

  answer(k) = k²(k²−1)/2 − 4(k−1)(k−2).

Check k = 3 by hand (36 − 8 = 28). The code is then five lines. This is the pattern you
will see all year: **a short proof, then a short program**.

## 5. Also today

- *Permutations*: a constructive problem. Find a pattern for n ≥ 4 and prove n = 2, 3 are
  impossible.
- *Palindrome Reorder*: count letters with an array of 26. When does a palindrome exist?
- *Trailing Zeros*: Legendre's formula. Note `p *= 5` inside the loop; ask yourself when
  `p` could overflow.

## 6. Practice

1. ORAC *Starter Set III*.
2. CSES *Permutations*, *Palindrome Reorder*, *Two Knights*, *Trailing Zeros*.
3. UG [Introduction to Data Structures](https://usaco.guide/bronze/intro-ds) ·
   [CS50x Week 2](https://cs50.harvard.edu/x/weeks/2/) (arrays).

**Checkpoint:** *Two Knights* derived on paper and coded in under 10 lines. You can explain
the difference between passing a vector by value and by reference.
