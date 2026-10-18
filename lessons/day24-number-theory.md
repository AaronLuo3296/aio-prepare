# Day 24: Number theory and combinatorics in code

**Goal:** modular arithmetic without overflow, fast exponentiation, modular inverses via
Fermat, sieves, divisor counting, and nCr mod p from factorial tables.
**Math bridge:** this is home ground: Fermat's little theorem, ℤ/pℤ is a field, and the
harmonic sum Σ N/d ≈ N ln N. The only new difficulty is the machine: integers that
silently overflow.

---

## 1. Modular arithmetic in C++

- `int` holds up to about 2.1·10⁹ and `long long` up to about 9.2·10¹⁸. With p = 10⁹ + 7,
  a product of two residues is below 10¹⁸, so it fits in `long long` but not in `int`.
- Reduce **after every** `+` and `*`. `(a * b) % p` with `int a, b` overflows *before*
  the `%`. Write `a * b % p` with `a` a `long long`.
- `%` of a negative number is negative in C++: `-3 % 5 == -3`. After subtracting, write
  `((a - b) % p + p) % p`.

## 2. Fast exponentiation and inverses

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD = 1e9 + 7;

ll power(ll a, ll b, ll m = MOD) {   // a^b mod m in O(log b)
    ll r = 1 % m;
    for (a %= m; b > 0; b >>= 1) {
        if (b & 1) r = r * a % m;
        a = a * a % m;
    }
    return r;
}

int main() {
    const int N = 1000000;
    vector<ll> fact(N + 1), inv_fact(N + 1);
    fact[0] = 1;
    for (int i = 1; i <= N; i++) fact[i] = fact[i - 1] * i % MOD;
    inv_fact[N] = power(fact[N], MOD - 2);        // Fermat: x^(p-2) = x^(-1)
    for (int i = N; i > 0; i--) inv_fact[i - 1] = inv_fact[i] * i % MOD;
    auto C = [&](int a, int b) { return fact[a] * inv_fact[b] % MOD * inv_fact[a - b] % MOD; };
    cout << power(2, 10) << " " << C(5, 3) << " " << C(1000000, 500000) << "\n";
}
```

Why the backwards loop works: 1/(i−1)! = i · 1/i!. It needs only **one** call to
`power` instead of N, so the whole table costs O(N + log p).

**Exponents live mod p − 1.** For p ∤ a, a^(p−1) ≡ 1, so a^e ≡ a^(e mod (p−1)). This is
CSES *Exponentiation II*: compute e = b^c mod (p − 1) **with modulus p − 1**, then a^e
mod p. (Reducing e mod p is a classic wrong answer.)

## 3. Sieves

- **Eratosthenes**: cross out multiples of each prime from p² upward. Takes
  O(N log log N) and gives all primes ≤ N.
- **Smallest prime factor** `spf[x]`: the same loop, but record the first prime that
  crosses x out. Then any x ≤ N factorises in O(log x) by repeated division by spf[x].
- **Loop over multiples**: `for d: for m = d, 2d, ...` costs Σ N/d = O(N log N). CSES
  *Counting Divisors* (cnt[m]++ for each divisor d) and *Common Divisors* (for d from
  large to small, count the input numbers that are multiples of d) are both this loop.

gcd: `std::gcd(a, b)` (header `<numeric>`, C++17) runs the Euclidean algorithm in
O(log min(a, b)).

## 4. Counting toolbox

| Count | Formula | Code |
|-------|---------|------|
| subsets of size k | C(n, k) | factorial tables |
| multisets of size k from n types | C(n + k − 1, k) | stars and bars |
| lattice paths a × b | C(a + b, a) | |
| derangements | D(n) = (n − 1)(D(n−1) + D(n−2)) | a DP |
| Catalan | C(2n, n)/(n + 1) | multiply by inverse of n + 1 |

If C(n, k) is needed for n ≤ 5000 only, Pascal's triangle (O(n²), no inverses) is simpler
and works for any modulus.

## 5. Practice

1. CSES *Exponentiation*, *Exponentiation II*, *Counting Divisors*, *Common Divisors*,
   *Binomial Coefficients*.
2. Read CPH ch. 21–22. Skim; most of it you know.
3. If you finish early: CSES *Creating Strings II* and *Distributing Apples* (same
   factorial tables).

Reference solutions: `solutions/cses/` (`exponentiation`, `exponentiation-ii`,
`counting-divisors`, `common-divisors`, `binomial-coefficients`).

**Checkpoint:** precompute factorials and inverse factorials up to 10⁶ in O(N) from memory,
and explain why `inv_fact[i-1] = inv_fact[i] * i`.
