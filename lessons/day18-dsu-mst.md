# Day 18: Disjoint Set Union and minimum spanning trees

**Goal:** a DSU with path compression and union by size, and Kruskal's algorithm.
**Math bridge:** a DSU maintains an equivalence relation under "merge two classes". The
MST cut property is an exchange argument: the cheapest edge across any cut belongs to
some minimum spanning tree.

---

## 1. DSU

Each set is a tree of parent pointers; the root names the set.

```cpp
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent, size;
    DSU(int n) : parent(n + 1), size(n + 1, 1) { iota(parent.begin(), parent.end(), 0); }
    int find(int x) {
        while (parent[x] != x) x = parent[x] = parent[parent[x]];   // path compression
        return x;
    }
    bool unite(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;                 // already in the same set
        if (size[a] < size[b]) swap(a, b);        // union by size: small under large
        parent[b] = a;
        size[a] += size[b];
        return true;
    }
};

int main() {
    DSU d(5);
    d.unite(1, 2);
    d.unite(3, 4);
    d.unite(2, 4);
    cout << (d.find(1) == d.find(3)) << " " << d.size[d.find(1)] << "\n";   // 1 4
}
```

Why union by size helps: a vertex's depth increases only when its set at least doubles in
size, so depth ≤ log₂ N. Path compression makes it practically constant (amortised
inverse-Ackermann, CPH ch. 15.2). Copy this struct into your template.

CSES *Road Construction*: after each new road, print the number of components and the
largest one. Every successful `unite` lowers the component count by 1.

## 2. Kruskal's algorithm

Sort edges by weight, then take each edge whose endpoints are in different sets. Stop
after N − 1 edges. If you can't reach N − 1, the graph is disconnected.

**Cut property.** Let e be the cheapest edge crossing a cut (S, V∖S). Then some MST
contains e.
**Proof.** Take an MST T without e. Adding e to T creates a cycle, and that cycle crosses
the cut at least twice, so it contains another crossing edge f with w(f) ≥ w(e). Then
T + e − f is a spanning tree of weight ≤ w(T). ∎

Kruskal adds an edge exactly when it is the cheapest edge across the cut "its endpoint's
component vs everything else", so every edge it takes is safe.

## 3. Practice

1. CSES *Road Reparation* (Kruskal; print IMPOSSIBLE if disconnected; total cost needs
   `long long`), *Road Construction* (DSU only).
2. Read CPH ch. 15, UG [DSU](https://usaco.guide/gold/dsu) and [MST](https://usaco.guide/gold/mst),
   and CPA [DSU](https://cp-algorithms.com/data_structures/disjoint_set_union.html) and
   [Kruskal with DSU](https://cp-algorithms.com/graph/mst_kruskal_with_dsu.html).

Reference solutions: `solutions/cses/` (`road-reparation`, `road-construction`).

**Checkpoint:** prove the cut property in five lines, and explain why union by size keeps
the depth at most log₂ N.
