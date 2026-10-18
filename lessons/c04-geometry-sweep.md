# Phase C.4: Geometry and sweep line

*Months 7–12, [roadmap](../plan/after-30-days.md#phase-c-months-712-ioi-toolkit-part-2-and-full-past-papers).
About two weeks.*

**Goal:** exact integer geometry with the cross product (orientation, segment
intersection, polygon area, convex hull), and the sweep-line pattern: sort events, move
a line across the plane, keep a data structure of what the line currently crosses.
**Math bridge:** the cross product (b − a) × (c − a) is twice the signed area of triangle
abc, a 2×2 determinant. Its sign is the orientation, and the shoelace formula is the sum
of these determinants around the polygon. Pick's theorem (A = i + b/2 − 1) links area to
lattice points. A sweep line is induction along the x-axis: the invariant is "the data
structure describes the cross-section at the current x".

**Read:** CPH ch. 29–30 · CPA [geometry basics](https://cp-algorithms.com/geometry/basic-geometry.html),
[convex hull](https://cp-algorithms.com/geometry/convex-hull.html).

---

## 1. Stay in integers

Contest geometry fails through **floating-point error** and **overflow**, not through
hard mathematics.

- With integer input, decide everything with cross and dot products in integers. Never
  compute angles or slopes as doubles to compare them.
- Coordinates up to 10⁹ give differences up to 2·10⁹, so one product is up to 4·10¹⁸ and
  a cross product up to 8·10¹⁸. That fits in `long long` (9.2·10¹⁸) with almost no
  margin. Any sum of such terms needs `__int128` (*Polygon Area*).
- Use doubles only for output that must be fractional, and compare them with an epsilon.

## 2. The primitives

```cpp
using ll = long long;
struct P { ll x, y; };
ll cross(P o, P a, P b) { return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x); }
```

- **Orientation** (*Point Location Test*): sign of cross(p1, p2, p3). Positive = left
  turn.
- **Segment intersection** (*Line Segment Intersection*): proper crossing iff each
  segment's endpoints are strictly on opposite sides of the other's line. Otherwise check
  the four "endpoint lies on the other segment" cases (cross = 0 and inside the bounding
  box). Collinear overlapping segments are caught by those cases.
- **Area** (*Polygon Area*): 2A = |Σ cross(0, pᵢ, pᵢ₊₁)|, the shoelace formula.
- **Point in polygon:** cast a ray and count edge crossings, handling the "on the
  boundary" case first.

## 3. Convex hull

Andrew's monotone chain: sort by (x, y), build the lower hull left to right and the upper
hull right to left. Each time, pop the last point while it makes a wrong turn. O(n log n).

The detail that decides correctness is **collinear points**. *Convex Hull* asks for every
point on the boundary, so pop only on a strict right turn (cross < 0). To get only the
corners, pop on cross ≤ 0. The reference tests use points on a tiny grid, so collinear
triples are common, and compare against a brute force that tests every pair of points as
a supporting line.

Uses: farthest pair (rotating calipers on the hull), the lower envelope in the convex
hull trick ([C.3](c03-dp-optimisations.md)), "which points can be extreme in some
direction".

## 4. Sweep line

The pattern: turn the objects into **events** sorted by x, process them in order, and keep
the active objects in a `set`, Fenwick tree or segment tree keyed by y.

| Problem | Events | Structure |
|---------|--------|-----------|
| *Intersection Points* (horizontal and vertical segments) | horizontal start/end, vertical at x | Fenwick tree over y: count active horizontals in [y₁, y₂] |
| *Area of Rectangles* (union area) | left and right edges | segment tree over compressed y: covered length |
| *Minimum Euclidean Distance* (closest pair) | points by x | `set` by y of points within distance d of the line |
| *Restaurant Customers* (Day 9) | arrivals and departures | a counter |

The common bugs: ties between events at the same x (decide whether a segment that ends at
x still intersects a vertical segment at x), and forgetting to compress coordinates.

## 5. Practice

1. CSES *Point Location Test*, *Line Segment Intersection*, *Polygon Area*, *Convex Hull*
   (reference solutions below).
2. CSES *Point in Polygon*, *Polygon Lattice Points* (Pick's theorem plus gcd for boundary
   points), *Minimum Euclidean Distance*, *Intersection Points*, *Area of Rectangles*.
3. Check the current [IOI syllabus](https://ioinformatics.org/page/syllabus/12) for which
   geometry topics are in scope. The sweep-line pattern is useful far beyond geometry
   either way.

Reference solutions: `solutions/cses/` (`point-location-test`,
`line-segment-intersection`, `polygon-area`, `convex-hull`).

**Checkpoint:** *Line Segment Intersection* and *Convex Hull* accepted first try, with
your own tests for collinear and touching cases.
