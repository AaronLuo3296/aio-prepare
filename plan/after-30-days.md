# After the 30 Days: Road to the IOI

The bootcamp makes a strong mathematician AIO-competitive. IOI-level performance typically
takes another **6–18 months** of steady work. This roadmap is ordered by dependency. Move
on when the checkpoint is met, not when the calendar says so.

## Weekly rhythm (≈10–12 h/week alongside school)

| When | What |
|------|------|
| 1 contest / week | [Codeforces](https://codeforces.com/) Div. 2/3 or [AtCoder](https://atcoder.jp/contests/archive) ABC/ARC, live or virtual |
| Within 48 h | **Upsolve**: every problem you could not solve, up to one level above your limit |
| 3–4 sessions | Topic study from the phase below + its problem list |
| Weekly | Review the error log; re-solve one old failure from a blank file |

Upsolving matters more than the contest itself. Most improvement happens there.

## Phase A (months 2–3): finish the core

- Complete the remaining CSES sections from the plan: *Sorting and Searching*, *Dynamic
  Programming*, *Graph Algorithms*, *Range Queries*, *Tree Algorithms*
  ([problem list](https://cses.fi/problemset/list/)).
- Work through every module of UG [Silver](https://usaco.guide/silver) and
  [Gold](https://usaco.guide/gold) not covered in the bootcamp.
- Finish the [AtCoder Educational DP Contest](https://atcoder.jp/contests/dp) (A–Z).
- **Checkpoint:** a full recent AIO Senior paper at near-full marks under exam conditions.

## Phase B (months 4–6): IOI toolkit, part 1

| Topic | Read | Notes |
|-------|------|-------|
| Strings: hashing, prefix function, Z-function | CPH ch. 26 · CPA [hashing](https://cp-algorithms.com/string/string-hashing.html), [prefix function](https://cp-algorithms.com/string/prefix-function.html), [Z](https://cp-algorithms.com/string/z-function.html) | hashing = polynomials mod p |
| Strongly connected components, 2-SAT | CPH ch. 17 · CPA [SCC](https://cp-algorithms.com/graph/strongly-connected-components.html), [2-SAT](https://cp-algorithms.com/graph/2SAT.html) | 2-SAT = implication graph of a logic formula |
| Lazy propagation, segment tree variants | CPH ch. 28 · UG [Segment Tree extensions](https://usaco.guide/plat/segtree-ext) | |
| Square-root decomposition | CPH ch. 27 · UG [Sqrt](https://usaco.guide/plat/sqrt) | |
| Game theory (Sprague–Grundy) | CPH ch. 25 | home ground for olympiad mathematicians |
| Interactive & function-signature tasks | IOI past problems on [oj.uz](https://oj.uz/problems/source/22) | practise the grader format |

- **Checkpoint:** solve IOI problems from 2010–2015 for most subtasks. Codeforces Div. 2 C
  solved reliably in contest.

## Phase C (months 7–12): IOI toolkit, part 2 and full past papers

| Topic | Read |
|-------|------|
| Heavy-light decomposition, centroid decomposition | CPH ch. 18 · UG [HLD](https://usaco.guide/plat/hld), [Centroid](https://usaco.guide/plat/centroid) |
| Flows and matchings | CPH ch. 20 |
| DP optimisations: convex hull trick, divide & conquer, bitset | CPA [CHT](https://cp-algorithms.com/geometry/convex_hull_trick.html) · UG [Platinum](https://usaco.guide/plat) |
| Geometry and sweep line | CPH ch. 29–30 |
| Beyond Platinum | UG [Advanced](https://usaco.guide/adv/) |

- Sit **full IOI days as virtual contests** (5 h, 3 problems) on
  [oj.uz](https://oj.uz/problems/source), which also archives many national and regional
  olympiads. Use those as additional full-length practice papers.
- **Checkpoint:** consistent partial scores on recent IOI days. You know which subtasks are
  "free" within the first 30 minutes.

## Australian pathway

AIO → AIIO (invitational) → national training school and team selection → IOI. Dates,
eligibility and formats change. Check the [Australian Maths Trust](https://www.amt.edu.au/)
and [ORAC](https://orac2.info/hub/competitions/) for the current year.

## Mindset notes for mathematicians

- In contest, **a correct-but-unproven greedy that passes stress tests is worth full
  marks**. Prove things afterwards, during upsolving.
- Implementation speed is a trainable skill: re-type standard structures (DSU, segment tree,
  Dijkstra) from memory until each takes under 10 minutes.
- Partial credit is real credit. A rigorous mathematician's instinct to "solve it fully or
  not at all" costs points at the IOI.
