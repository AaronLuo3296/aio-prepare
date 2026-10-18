# 30-Day Bootcamp: From Olympiad Maths to Informatics Olympiad

**For:** high-school students at IMO P1/P4 → P2/P5 level with **no programming background**.
**Goal after 30 days:** fluent in contest C++. Can reliably solve the easy and medium
problems (and most subtasks) on a past AIO paper. Knows the core IOI-syllabus toolkit:
sorting, greedy, binary search, DP, graphs, trees, range queries and number theory.

> **Honest calibration.** Thirty days is enough for a strong mathematician to become
> *AIO-competitive*. IOI-level performance usually takes another 6–18 months of steady
> contest practice (see Day 30). The ideas will come fast for these students. Most of the
> time goes into implementation and debugging, so the plan is weighted that way.

Abbreviations: **CPH** = *Competitive Programmer's Handbook* ([PDF](https://cses.fi/book/book.pdf)) ·
**UG** = [USACO Guide](https://usaco.guide/) (modules embed short videos) ·
**CPA** = [cp-algorithms](https://cp-algorithms.com/) ·
**JE** = Jeff Erickson, [*Algorithms*](https://jeffe.cs.illinois.edu/teaching/algorithms/) ·
**6.006** = [MIT 6.006 lecture videos](https://ocw.mit.edu/courses/6-006-introduction-to-algorithms-spring-2020/video_galleries/lecture-videos/) ·
**CSES** = [CSES Problem Set](https://cses.fi/problemset/) · **ORAC** = [AIO trainer](https://orac2.info/learn/) ·
**ADP** = [AtCoder Educational DP Contest](https://atcoder.jp/contests/dp).

---

## Daily rhythm (~3.5 h)

| Block | Time | What |
|-------|------|------|
| Read | 30–40 min | The CPH chapter / UG module for the day |
| Watch | 20–30 min | Optional; use it when the reading did not click |
| Prove | 10 min | Before coding each problem, write 2–3 lines: idea, why it is correct, complexity |
| Code | 2–2.5 h | The Practice list, in order. Spend at most 25 min stuck, then read a hint and move on |
| Log | 15 min | Error log: every wrong answer gets one line (bug type + lesson) |

**Constraint cheat-sheet** (assume ~10⁸ simple ops/sec):
N ≤ 10 → N! · N ≤ 20 → 2ᴺ · N ≤ 500 → N³ · N ≤ 5 000 → N² · N ≤ 2·10⁵ → N log N · N ≤ 10⁷ → N.

---

## Week 1: Learning to program (C++ from zero)

### Day 1: Setup, first programs, input/output
- **Lesson notes:** [lessons/day01-setup-and-first-programs.md](../lessons/day01-setup-and-first-programs.md)
- **Goal:** compile and run a program. Read input and print output. Submit to a judge.
- **Math bridge:** a program is a precise algorithm, like a constructive proof with no
  gaps a machine has to fill in.
- **Read:** UG [Intro to Competitive Programming](https://usaco.guide/general/intro-cp),
  [Running Code Online](https://usaco.guide/general/running-code-online) ·
  [learncpp.com](https://www.learncpp.com/) chapters 0–1.
- **Watch:** [CS50x](https://cs50.harvard.edu/x/) Week 0 (Scratch: computational thinking).
- **Practice:** ORAC *Starter Set I* (via [orac2.info/learn](https://orac2.info/learn/)) ·
  CSES *Weird Algorithm* (the Collatz map. Use `long long` and see why).
- **Checkpoint:** you can explain `int` vs `long long` overflow with a concrete number.

### Day 2: Conditionals, loops, integer arithmetic
- **Lesson notes:** [lessons/day02-control-flow.md](../lessons/day02-control-flow.md)
- **Goal:** `if`/`else`, `for`, `while`, `%` and integer division, overflow.
- **Math bridge:** a loop invariant is an induction hypothesis. State it for each loop you write.
- **Read:** learncpp chapters on control flow · CPH ch. 1 (sections on C++ code, I/O, working with numbers).
- **Watch:** CS50x Week 1 (C, which has almost the same syntax as C++ here).
- **Practice:** ORAC *Starter Set II* · CSES *Missing Number*, *Repetitions*,
  *Increasing Array*, *Number Spiral*.
- **Checkpoint:** *Number Spiral* solved with a closed-form formula, not a simulation.

### Day 3: Arrays, vectors, strings, functions
- **Lesson notes:** [lessons/day03-arrays-strings-functions.md](../lessons/day03-arrays-strings-functions.md)
- **Goal:** `vector`, `string`, writing and calling functions, passing by reference.
- **Math bridge:** a function is a function. Arrays are sequences aₙ, and indexing from 0
  is a shift of index.
- **Read:** UG [Introduction to Data Structures](https://usaco.guide/bronze/intro-ds) ·
  learncpp chapters on functions, `std::vector` and `std::string`.
- **Watch:** CS50x Week 2 (Arrays).
- **Practice:** ORAC *Starter Set III* · CSES *Permutations*, *Palindrome Reorder*,
  *Two Knights* (count attacking pairs: pure combinatorics), *Trailing Zeros* (Legendre's formula).
- **Checkpoint:** *Two Knights* derived on paper first, then coded in under 10 lines.

### Day 4: Time complexity and reading constraints
- **Lesson notes:** [lessons/day04-time-complexity.md](../lessons/day04-time-complexity.md)
- **Goal:** Big-O. Predict whether a solution passes **before** coding it.
- **Math bridge:** asymptotics are growth rates. Counting operations is double counting.
- **Read:** CPH ch. 2 · UG [Time Complexity](https://usaco.guide/bronze/time-comp) ·
  UG [Fast I/O](https://usaco.guide/general/fast-io).
- **Watch:** 6.006 Lecture 1 (Algorithms and Computation).
- **Practice:** CSES *Bit Strings* (2ⁿ mod 10⁹+7), *Coin Piles*, *Two Sets*
  (constructive), *Gray Code*.
- **Checkpoint:** for each problem so far, write the complexity and the largest N it handles.

### Day 5: Simulation and complete search
- **Lesson notes:** [lessons/day05-complete-search.md](../lessons/day05-complete-search.md)
- **Goal:** turn a statement into code faithfully. Enumerate all cases.
- **Math bridge:** case analysis. A computer will happily check 2²⁰ cases for you.
- **Read:** UG [Simulation](https://usaco.guide/bronze/simulation),
  [Basic Complete Search](https://usaco.guide/bronze/intro-complete) · CPH ch. 5.1–5.2.
- **Practice:** ORAC *Starter Set IV* · CSES *Apple Division* (2ⁿ subsets with bitmasks),
  *Creating Strings* (`next_permutation`).
- **Checkpoint:** enumerate all subsets of {0..n−1} with a bitmask loop from memory.

### Day 6: Recursion and backtracking
- **Lesson notes:** [lessons/day06-recursion-backtracking.md](../lessons/day06-recursion-backtracking.md)
- **Goal:** recursive functions, generating permutations and subsets, pruning.
- **Math bridge:** recursion *is* strong induction. Base case plus inductive step equals
  base case plus recursive call.
- **Read:** JE ch. 1 (Recursion) and ch. 2 (Backtracking) ·
  UG [Complete Search with Recursion](https://usaco.guide/bronze/complete-rec) · CPH ch. 5.3–5.4.
- **Watch:** [Abdul Bari](https://www.youtube.com/@abdul_bari): recursion and backtracking videos (e.g. N-Queens).
- **Practice:** CSES *Tower of Hanoi*, *Chessboard and Queens*; re-solve *Permutations* recursively.
- **Checkpoint:** prove the Tower of Hanoi move count 2ⁿ−1 and match it to your recursion tree.

### Day 7: Checkpoint (debugging, stress testing, first AIO taste)
- **Lesson notes:** [lessons/day07-debugging-and-first-aio.md](../lessons/day07-debugging-and-first-aio.md)
- **Goal:** learn to find bugs systematically. First contact with real AIO problems.
- **Skills:** compile with `-Wall -Wextra -fsanitize=address,undefined`. Print-debugging.
  Write a brute-force solution plus a random input generator, then compare outputs in a loop.
- **Practice:** pick the **first two problems** from 2–3 different years in
  [ORAC AIO Sets](https://orac2.info/hub/aio/). Aim for every subtask you can get.
- **Checkpoint:** an error log with at least 10 entries. Note the most common bug type
  (usually off-by-one or overflow).

---

## Week 2: Core techniques

### Day 8: Sorting and the standard library
- **Lesson notes:** [lessons/day08-sorting-and-stl.md](../lessons/day08-sorting-and-stl.md)
- **Goal:** `sort` with custom comparators, `set`, `map`, `multiset`, `pair`.
- **Math bridge:** ordering creates structure (extremal principle). Many problems become
  trivial once sorted.
- **Read:** CPH ch. 3–4 · UG [Intro to Sorting](https://usaco.guide/bronze/intro-sorting).
- **Watch:** 6.006 Lecture 3 (Sets and Sorting) · [VisuAlgo sorting](https://visualgo.net/en).
- **Practice:** CSES *Distinct Numbers*, *Apartments*, *Ferris Wheel*, *Concert Tickets* (multiset).
- **Checkpoint:** explain why `sort` is O(N log N) and why comparison sorting cannot beat it
  (decision-tree counting argument).

### Day 9: Greedy algorithms and exchange arguments
- **Lesson notes:** [lessons/day09-greedy.md](../lessons/day09-greedy.md)
- **Goal:** spot greedy structure and **prove** it before trusting it.
- **Math bridge:** this is the exchange argument / extremal principle you already know.
  Greedy without proof is guessing.
- **Read:** CPH ch. 6 · JE ch. 4 (Greedy Algorithms) ·
  UG [Intro to Greedy](https://usaco.guide/bronze/intro-greedy),
  [Greedy with Sorting](https://usaco.guide/silver/greedy-sorting).
- **Practice:** CSES *Movie Festival*, *Restaurant Customers* (sweep), *Stick Lengths*
  (median minimises the L1 distance; prove it), *Tasks and Deadlines*.
- **Checkpoint:** a written exchange-argument proof for *Movie Festival*.

### Day 10: Prefix sums and difference arrays
- **Lesson notes:** [lessons/day10-prefix-sums.md](../lessons/day10-prefix-sums.md)
- **Goal:** O(1) range sums after O(N) preprocessing. 2D prefix sums.
- **Math bridge:** telescoping sums. Pigeonhole on prefix sums mod k.
- **Read:** UG [Prefix Sums](https://usaco.guide/silver/prefix-sums) · CPH ch. 9.1.
- **Practice:** CSES *Static Range Sum Queries*, *Subarray Sums I*, *Subarray Sums II*
  (`map` of prefix sums), *Subarray Divisibility* (pigeonhole!).
- **Checkpoint:** solve *Subarray Divisibility* and name the classical olympiad lemma it uses.

### Day 11: Two pointers and binary search
- **Lesson notes:** [lessons/day11-two-pointers-binary-search.md](../lessons/day11-two-pointers-binary-search.md)
- **Goal:** two pointers on sorted data. Binary search on a monotone predicate
  ("binary search the answer").
- **Math bridge:** monotone functions and the intermediate value idea. Bisection.
- **Read:** UG [Two Pointers](https://usaco.guide/silver/two-pointers),
  [Binary Search](https://usaco.guide/silver/binary-search) ·
  CPA [Binary search](https://cp-algorithms.com/num_methods/binary_search.html).
- **Watch:** [Errichto](https://www.youtube.com/@Errichto): binary search lecture.
- **Practice:** CSES *Sum of Two Values*, *Maximum Subarray Sum* (Kadane), *Playlist*,
  *Factory Machines* (binary search on the answer).
- **Checkpoint:** write a binary search with the invariant "lo is always bad, hi is always
  good" and never get stuck in an infinite loop.

### Day 12: Dynamic programming I
- **Lesson notes:** [lessons/day12-dp-intro.md](../lessons/day12-dp-intro.md)
- **Goal:** state, transition, base case, order of evaluation. Memoisation vs tabulation.
- **Math bridge:** DP is recurrences plus induction. You have solved "count the number of
  ways…" problems with recurrences for years. Now the computer evaluates them.
- **Read:** CPH ch. 7 · JE ch. 3 (Dynamic Programming) · UG [Intro to DP](https://usaco.guide/gold/intro-dp).
- **Watch:** 6.006 Lectures 15–16 (recursive algorithms, the SRTBOT framework, DP subproblems) ·
  Errichto's DP lectures.
- **Practice:** CSES *Dice Combinations*, *Minimizing Coins*, *Coin Combinations I*,
  *Coin Combinations II* (ordered vs unordered: why the loop order matters) ·
  *Removing Digits* · ADP *A: Frog 1*, *B: Frog 2*.
- **Checkpoint:** explain the Coin Combinations I/II difference as a bijection argument.

### Day 13: Dynamic programming II (knapsack, grids, sequences)
- **Lesson notes:** [lessons/day13-dp-knapsack-grids-sequences.md](../lessons/day13-dp-knapsack-grids-sequences.md)
- **Goal:** 2D DP, knapsack, LCS and edit distance, LIS in O(N log N).
- **Math bridge:** lattice-path counting (grid DP), extremal subsequences (Erdős–Szekeres ↔ LIS).
- **Read:** UG [Knapsack](https://usaco.guide/gold/knapsack),
  [Paths on Grids](https://usaco.guide/gold/paths-grids),
  [LIS](https://usaco.guide/gold/lis).
- **Practice:** CSES *Grid Paths* (DP section), *Book Shop*, *Array Description*,
  *Edit Distance* · ADP *D: Knapsack 1*, *F: LCS*.
- **Checkpoint:** reduce knapsack memory from O(NW) to O(W) and explain why iterating
  W downwards is required.

### Day 14: Mock contest #1
- **Lesson notes:** [lessons/day14-mock-contest-1.md](../lessons/day14-mock-contest-1.md)
- **Format:** 3 hours, timed, one full AIO paper from [ORAC AIO Sets](https://orac2.info/hub/aio/)
  (choose an Intermediate-level year). No notes except your own templates.
- **Afterwards:** upsolve every problem (read official solutions on ORAC where available).
  Update the error log.
- **Checkpoint:** score recorded. List which topics cost the most points.

---

## Week 3: Graphs and trees

### Day 15: Graph representation, DFS, BFS
- **Goal:** adjacency lists, DFS (recursive and iterative), BFS, connected components, grid flood fill.
- **Math bridge:** everything from your graph-theory background. The handshake lemma explains
  why adjacency lists cost O(N+M).
- **Read:** CPH ch. 11–12 · UG [Intro to Graphs](https://usaco.guide/bronze/intro-graphs),
  [Graph Traversal](https://usaco.guide/silver/graph-traversal),
  [Flood Fill](https://usaco.guide/silver/flood-fill) ·
  CPA [BFS](https://cp-algorithms.com/graph/breadth-first-search.html),
  [DFS](https://cp-algorithms.com/graph/depth-first-search.html).
- **Watch:** 6.006 Lectures 9–10 (BFS, DFS) · [VisuAlgo graph traversal](https://visualgo.net/en).
- **Practice:** CSES *Counting Rooms*, *Building Roads*, *Message Route*, *Labyrinth* (path reconstruction).
- **Checkpoint:** prove BFS gives shortest paths in unweighted graphs (induction on distance layers).

### Day 16: Bipartiteness, cycles, multi-source BFS
- **Goal:** 2-colouring, cycle detection with parent tracking, BFS from many sources.
- **Math bridge:** bipartite ⇔ no odd cycle (you know the proof; now the BFS layers *are* the proof).
- **Practice:** CSES *Building Teams*, *Round Trip*, *Monsters* (multi-source BFS).
- **Checkpoint:** *Round Trip* outputs an actual cycle, not just "yes".

### Day 17: Weighted shortest paths
- **Goal:** Dijkstra with a priority queue, Bellman–Ford, Floyd–Warshall. Know when each applies.
- **Math bridge:** Dijkstra's correctness is an extremal argument (the closest unfinalised
  vertex can't be improved).
- **Read:** CPH ch. 13 · UG [Shortest Paths](https://usaco.guide/gold/shortest-paths) ·
  CPA [Dijkstra](https://cp-algorithms.com/graph/dijkstra.html).
- **Watch:** 6.006 Lectures 11–13 (weighted shortest paths, Bellman–Ford, Dijkstra).
- **Practice:** CSES *Shortest Routes I*, *Shortest Routes II*, *Flight Discount* (state-expanded graph).
- **Checkpoint:** find a graph with a negative edge where Dijkstra fails, by hand.

### Day 18: Disjoint Set Union and minimum spanning trees
- **Goal:** DSU with path compression and union by size. Kruskal's algorithm.
- **Math bridge:** the MST cut property is an exchange argument. DSU maintains an equivalence relation.
- **Read:** CPH ch. 15 · UG [DSU](https://usaco.guide/gold/dsu), [MST](https://usaco.guide/gold/mst) ·
  CPA [DSU](https://cp-algorithms.com/data_structures/disjoint_set_union.html),
  [Kruskal with DSU](https://cp-algorithms.com/graph/mst_kruskal_with_dsu.html).
- **Practice:** CSES *Road Reparation*, *Road Construction*.
- **Checkpoint:** prove the cut property in five lines.

### Day 19: Directed acyclic graphs
- **Goal:** topological sort (Kahn and DFS), DP on DAGs, longest/shortest paths in a DAG.
- **Math bridge:** a partial order has a linear extension. DP needs exactly such an order.
- **Read:** CPH ch. 16 · UG [Topological Sort](https://usaco.guide/gold/toposort) ·
  CPA [Topological sort](https://cp-algorithms.com/graph/topological-sort.html).
- **Practice:** CSES *Course Schedule*, *Longest Flight Route*, *Game Routes* · ADP *G: Longest Path*.
- **Checkpoint:** explain why *every* DP is a DAG of states.

### Day 20: Trees and tree DP
- **Goal:** rooting a tree, subtree sizes, diameter, DP on trees, rerooting idea.
- **Math bridge:** trees: N−1 edges, unique paths, leaves exist (extremal). Diameter via
  "farthest from the farthest".
- **Read:** CPH ch. 14.
- **Practice:** CSES *Subordinates*, *Tree Diameter*, *Tree Distances I*, *Tree Matching* ·
  ADP *P: Independent Set*.
- **Checkpoint:** prove the double-BFS diameter algorithm is correct.

### Day 21: Mock contest #2
- **Format:** 3 hours, a Senior-level AIO paper from [ORAC AIO Sets](https://orac2.info/hub/aio/).
- **Afterwards:** upsolve. Compare with mock #1: which error-log categories shrank?

---

## Week 4: Range queries, number theory, IOI on-ramp

### Day 22: Fenwick trees, segment trees, sparse tables
- **Goal:** point-update/range-query in O(log N). Static RMQ in O(1).
- **Math bridge:** binary representations (the low bit, `i & -i`). Idempotent operations (min) allow overlapping ranges.
- **Read:** CPH ch. 9, 28 · UG [Point Update Range Sum](https://usaco.guide/gold/PURS) ·
  CPA [Fenwick](https://cp-algorithms.com/data_structures/fenwick.html),
  [Segment tree](https://cp-algorithms.com/data_structures/segment_tree.html),
  [Sparse table](https://cp-algorithms.com/data_structures/sparse-table.html).
- **Watch:** [VisuAlgo segment tree / Fenwick tree](https://visualgo.net/en).
- **Practice:** CSES *Static Range Minimum Queries*, *Dynamic Range Sum Queries*,
  *Dynamic Range Minimum Queries*, *Range Xor Queries*.
- **Checkpoint:** a bottom-up segment tree from memory in under 15 minutes.

### Day 23: Tree queries (Euler tour, binary lifting, LCA)
- **Goal:** flatten a tree into an array. Jump 2ᵏ ancestors. LCA. Distances on trees.
- **Math bridge:** every integer is a sum of distinct powers of 2 (binary lifting = fast exponentiation on ancestors).
- **Read:** CPH ch. 18 · UG [Euler Tour](https://usaco.guide/gold/tree-euler),
  [Binary Jumping](https://usaco.guide/plat/binary-jump) ·
  CPA [LCA with binary lifting](https://cp-algorithms.com/graph/lca_binary_lifting.html).
- **Practice:** CSES *Company Queries I*, *Company Queries II*, *Distance Queries*, *Subtree Queries*.
- **Checkpoint:** dist(u,v) = depth(u)+depth(v)−2·depth(lca). Prove it and use it.

### Day 24: Number theory and combinatorics in code
- **Goal:** modular arithmetic, fast exponentiation, modular inverses (Fermat), sieve,
  divisor counting, nCr mod p with factorial tables.
- **Math bridge:** this is home ground. Expect to finish fast and spend the extra time on the
  last problems.
- **Read:** CPH ch. 21–22 · UG [Divisibility](https://usaco.guide/gold/divisibility),
  [Modular Arithmetic](https://usaco.guide/gold/modular),
  [Combinatorics](https://usaco.guide/gold/combo) ·
  CPA [Binary exponentiation](https://cp-algorithms.com/algebra/binary-exp.html),
  [Sieve](https://cp-algorithms.com/algebra/sieve-of-eratosthenes.html),
  [Modular inverse](https://cp-algorithms.com/algebra/module-inverse.html).
- **Practice:** CSES *Exponentiation*, *Exponentiation II* (reduce the exponent mod p−1: why?),
  *Counting Divisors*, *Common Divisors*, *Binomial Coefficients*.
- **Checkpoint:** precompute factorials and inverse factorials up to 10⁶ in O(N).

### Day 25: Bit manipulation and bitmask DP
- **Goal:** bit operations, DP over subsets (N ≤ 20).
- **Math bridge:** subsets ↔ binary strings. Inclusion–exclusion over masks.
- **Read:** CPH ch. 10 · UG [Bitmask DP](https://usaco.guide/gold/dp-bitmasks).
- **Practice:** CSES *Hamiltonian Flights*, *Elevator Rides* · ADP *O: Matching*.
- **Checkpoint:** explain why *Hamiltonian Flights* is O(2ᴺ·N²) and why that fits N = 20.

### Day 26: The IOI format
- **Goal:** understand IOI-style tasks: you implement a *function* called by a grader (not
  stdin/stdout). Some tasks are interactive, output-only, or scored per subtask.
- **Read:** [IOI syllabus](https://ioinformatics.org/page/syllabus/12) (note which topics you
  have now covered) · [IOI contests archive](https://ioinformatics.org/page/contests/10).
- **Practice ([oj.uz IOI archive](https://oj.uz/problems/source/22)):** suggested gentle
  starters: IOI 2011 *Rice Hub* (binary search + prefix sums), IOI 2016 *Detecting
  Molecules* (sorting + two pointers), IOI 2018 *Combo* (interactive). Take all the subtasks
  you can, even if the full solution is out of reach.
- **Checkpoint:** a template that compiles against a grader stub.

### Day 27: Mock contest #3 (full AIO simulation)
- **Format:** the most recent AIO paper you have not seen, under strict exam conditions
  (3 h, one sitting, no internet).
- **Afterwards:** upsolve everything.

### Day 28: Consolidation
- Re-solve, **from a blank file**, five problems from your error log that you got wrong.
- Build your personal template file: fast I/O, DSU, Dijkstra, segment tree, mod-pow,
  BFS on grid, binary search on answer.
- Re-read the CPH chapters behind your two weakest error-log categories.

### Day 29: Mock contest #4
- Another unseen AIO Senior paper (or an [AtCoder Beginner Contest](https://atcoder.jp/) live
  or virtual, problems A–E). Upsolve.

### Day 30: Retrospective and roadmap
- Compare scores across mocks #1–#4. Update the error log summary.
- **What comes next** (full roadmap: [after-30-days.md](after-30-days.md))**, IOI track, roughly in order:** strings (CPH ch. 26: hashing, KMP/Z) →
  strongly connected components (CPH ch. 17) → lazy propagation and advanced segment trees
  (CPH ch. 28, UG [Segment Tree extensions](https://usaco.guide/plat/segtree-ext)) →
  square-root techniques (CPH ch. 27) → flows (CPH ch. 20) → geometry and sweep line
  (CPH ch. 29–30) → advanced DP optimisations (UG Platinum).
- **Habits:** one rated contest a week ([Codeforces](https://codeforces.com/) Div. 2/3 or
  AtCoder ABC/ARC), always followed by upsolving. Work through IOI problems on oj.uz by year.
  Work through the remaining CSES sections.
- **Pathway:** AIO → AIIO (invitational) → Australian training school / team selection → IOI.
  Check the [Australian Maths Trust](https://www.amt.edu.au/) for the current year's dates and rules.

---

## Progress tracker

| Week | Topic | CSES problems | Other | Mock score |
|------|-------|---------------|-------|------------|
| 1 | C++ basics, complexity, complete search | ~17 | ORAC Starter Sets I–IV, 2–3 AIO subtasks | — |
| 2 | Sorting, greedy, prefix sums, binary search, DP | ~25 | ADP A, B, D, F | #1: ___ |
| 3 | Graphs, shortest paths, DSU/MST, DAGs, trees | ~20 | ADP G, P | #2: ___ |
| 4 | Range queries, LCA, number theory, bitmasks, IOI | ~15 | ADP O, 3 IOI tasks | #3: ___ #4: ___ |

**Exit criteria:** about 80 CSES problems solved, every Week 1–4 checkpoint passed, and
mock scores trending upward with full marks on the first two problems of a Senior AIO paper.
