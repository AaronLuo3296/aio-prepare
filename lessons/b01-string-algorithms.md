# Phase B.1: Strings: prefix function, Z-function, hashing

*Months 4–6, [roadmap](../plan/after-30-days.md#phase-b-months-46-ioi-toolkit-part-1). About
two weeks.*

**Goal:** find every occurrence of a pattern in linear time, compute borders and periods,
and compare any two substrings in O(1) with polynomial hashing.
**Math bridge:** a *border* of s (a proper prefix that is also a suffix) and a *period*
p (s[i] = s[i+p] for all valid i) are the same object: s has a border of length b iff it
has period n − b. Hashing treats a string as a polynomial evaluated at a random point
mod a prime M. For a random base, two different strings of length L collide with
probability below L/M, because their difference is a nonzero polynomial of degree < L,
which has fewer than L roots mod M.

**Read:** CPH ch. 26 · CPA [prefix function](https://cp-algorithms.com/string/prefix-function.html),
[Z-function](https://cp-algorithms.com/string/z-function.html),
[hashing](https://cp-algorithms.com/string/string-hashing.html).

---

## 1. Prefix function

pi[i] = length of the longest proper border of s[0..i]. Key fact: the borders of a string
are exactly pi[n−1], pi[pi[n−1]−1], … (a border of a border is a border). So when s[i]
does not extend the current border k, fall back to the next shorter border, pi[k−1].

```cpp
#include <bits/stdc++.h>
using namespace std;

vector<int> prefix_function(const string &s) {
    vector<int> pi(s.size(), 0);
    for (int i = 1; i < (int)s.size(); i++) {
        int k = pi[i - 1];
        while (k > 0 && s[i] != s[k]) k = pi[k - 1];
        if (s[i] == s[k]) k++;
        pi[i] = k;
    }
    return pi;
}

int main() {
    for (int x : prefix_function("abcababcab")) cout << x << " ";   // 0 0 0 1 2 1 2 3 4 5
    cout << "\n";
}
```

**Why O(n):** k rises by at most 1 per step and each fallback lowers it, so the total
number of fallbacks is at most n (the same potential argument as the monotonic stack in
[A.1](a01-stacks-lis-multiset-greedy.md)).

**Pattern matching (KMP):** compute pi on `p + '#' + t`. The separator caps every value at
|p|, and pi[i] = |p| exactly where an occurrence ends.

## 2. Z-function

z[i] = length of the longest common prefix of s and s[i..]. The algorithm keeps the
rightmost window [l, r) that matches a prefix of s and reuses z[i − l] inside it. It is
also O(n). Periods fall out directly: p is a period iff z[p] = n − p (or p = n).

Prefix function and Z-function solve the same problems. Learn both, then pick one to use
in contest and know it cold.

## 3. Polynomial hashing

h(s[0..i)) = s₀·B^(i−1) + … + s_(i−1) (mod M), computed as a prefix array:
h[i+1] = h[i]·B + s[i]. Then the hash of any substring s[l..r) is
h[r] − h[l]·B^(r−l) (mod M), in O(1).

- Choose B **at random** at runtime. A fixed, well-known base can be attacked by
  hand-made tests (Codeforces "anti-hash" hacks).
- With M ≈ 10⁹ and ~10⁶ comparisons, the birthday bound makes a collision likely. Use
  M = 2⁶¹ − 1 with `__int128` multiplication, or two independent moduli.
- Hashing turns "longest X" problems into binary search plus O(1) comparisons: longest
  common prefix of two suffixes, longest repeated substring, palindrome checks (compare
  with the hash of the reversed string).

## 4. Practice

1. CSES *String Matching* (KMP), *Finding Borders* (prefix function chain), *Finding
   Periods* (Z-function). Reference solutions below.
2. CSES *String Algorithms*: *Minimal Rotation*, *Longest Palindrome* (Manacher, or
   hashing + binary search), *Required Substring* (KMP automaton + DP), *Palindrome
   Queries* (hashing + Fenwick tree), *Word Combinations* (trie + DP).
3. Solve *String Matching* a second time with hashing only. Compare the code length and
   think about which one you trust more under time pressure.

Reference solutions: `solutions/cses/` (`string-matching`, `finding-borders`,
`finding-periods`).

**Checkpoint:** write the prefix function from memory, prove its O(n) bound, and state the
collision probability of your hashing scheme for the input sizes of *Palindrome Queries*.
