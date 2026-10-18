# Day 8: Sorting and the standard library

**Goal:** sort anything (with your own order), and use the four containers that solve
half of all contest problems: `vector`, `set`/`multiset`, `map`, `pair`.
**Math bridge:** the extremal principle. Once data is sorted, "look at the smallest/largest
element" is free, and many problems become a single pass.

---

## 1. `sort` and comparators

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> a = {5, 1, 4, 1, 3};
    sort(a.begin(), a.end());                    // 1 1 3 4 5
    sort(a.rbegin(), a.rend());                  // 5 4 3 1 1  (descending)

    vector<pair<int, int>> p = {{2, 9}, {1, 7}, {2, 3}};
    sort(p.begin(), p.end());                    // by first, ties by second: (1,7) (2,3) (2,9)

    // Custom order: by second component. The comparator answers "must x come before y?"
    sort(p.begin(), p.end(), [](const pair<int, int>& x, const pair<int, int>& y) {
        return x.second < y.second;
    });
    for (auto [f, s] : p) cout << f << "," << s << " ";   // 2,3 1,7 2,9
    cout << "\n";
}
```

Rules for a comparator: it must be a **strict** order. Write `<`, never `<=`: with `<=`
an element "comes before itself", and `sort` may crash.

Trick worth knowing: store a pair in the order you want to sort by. To sort movies by end
time, store `(end, start)` and call plain `sort`.

## 2. Why O(N log N), and why no comparison sort beats it

`sort` does Θ(N log N) comparisons. Lower bound (a counting argument you will enjoy): a
comparison sort is a binary decision tree whose leaves must include all N! orderings, so its
depth is at least log₂(N!) ≥ (N/2)·log₂(N/2) = Ω(N log N). Read CPH ch. 3.

## 3. The containers

| Container | What it is | Key operations (cost) |
|-----------|-----------|------------------------|
| `vector<T>` | array that can grow | `v[i]`, `push_back` O(1) |
| `set<T>` | sorted, no duplicates | `insert`, `erase`, `count`, `lower_bound` O(log N) |
| `multiset<T>` | sorted, duplicates allowed | same, but `erase(value)` removes **all** copies |
| `map<K,V>` | sorted key → value | `m[k]` (creates k if absent!), `find`, `count` O(log N) |

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    multiset<int> s = {5, 3, 5, 8};
    s.erase(s.find(5));              // removes ONE 5   -> {3, 5, 8}
    auto it = s.upper_bound(6);      // first element > 6  -> 8
    --it;                            // the largest element <= 6  -> 5
    cout << *it << "\n";

    map<string, int> freq;
    for (string w : {"a", "b", "a"}) freq[w]++;
    for (auto [word, c] : freq) cout << word << ":" << c << " ";   // a:2 b:1 (sorted keys)
    cout << "\n";
}
```

- `lower_bound(x)`: first element **≥ x**. `upper_bound(x)`: first element **> x**.
  Both return `end()` if there is none. Never dereference `end()`.
- On CSES avoid `unordered_map` (adversarial tests make it slow). `map` is always safe.

## 4. Worked problem: CSES *Concert Tickets*

> n tickets with prices, m customers in order. Each customer names a maximum price and
> buys the most expensive ticket not above it (or gets nothing, print −1).

We need "largest element ≤ t, then delete it" fast, and prices repeat. That is exactly
`multiset` + `upper_bound` + one step back, as in the example above. Each customer costs
O(log n), total O((n + m) log n). The trap: `prices.erase(t)` deletes every ticket with
that price. Erase by iterator.

## 5. Practice

1. CSES *Distinct Numbers* (two ways: sort + count changes, or a `set`).
2. CSES *Apartments* (sort both lists, then walk them together).
3. CSES *Ferris Wheel* (pair the heaviest with the lightest; why is that safe?).
4. CSES *Concert Tickets*.
5. Read CPH ch. 3–4 and UG [Intro to Sorting](https://usaco.guide/bronze/intro-sorting).
   Watch 6.006 Lecture 3. Play with [VisuAlgo sorting](https://visualgo.net/en).

Reference solutions: `solutions/cses/` (`distinct-numbers`, `apartments`, `ferris-wheel`,
`concert-tickets`).

**Checkpoint:** explain the log₂(N!) lower bound to a friend in under two minutes, and
state when you would use `multiset` instead of `set`.
