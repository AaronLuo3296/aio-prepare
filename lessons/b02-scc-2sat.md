# Phase B.2: Strongly connected components and 2-SAT

*Months 4–6, [roadmap](../plan/after-30-days.md#phase-b-months-46-ioi-toolkit-part-1). About
one week.*

**Goal:** split a directed graph into strongly connected components (SCCs), use the
condensation DAG, and solve 2-SAT, which is satisfiability of a conjunction of clauses
with two literals each.
**Math bridge:** "u and v reach each other" is an equivalence relation, and its classes
are the SCCs. Contracting each class gives a DAG, so every directed graph is a DAG of SCCs.
2-SAT: the clause (a ∨ b) is the same as the two implications ¬a ⇒ b and ¬b ⇒ a. The
formula is unsatisfiable iff some x and ¬x imply each other, i.e. lie in the same SCC of
the implication graph.

**Read:** CPH ch. 17 · CPA [SCC](https://cp-algorithms.com/graph/strongly-connected-components.html),
[2-SAT](https://cp-algorithms.com/graph/2SAT.html).

---

## 1. Kosaraju's algorithm

1. DFS the graph and record each node when it **finishes**.
2. Process nodes in **reverse** finishing order. Each unvisited node starts a flood fill
   in the **reversed** graph, and everything that flood reaches is one SCC.

Why it works: the node that finishes last lies in a *source* SCC of the condensation. In
the reversed graph that SCC is a sink, so the flood cannot leak out of it. Remove it and
repeat. A side effect: components are numbered in **topological order** of the
condensation (sources first).

Implementation notes:

- Iterative DFS with an index per node (`it[u]` = next edge to try) produces the finishing
  order without recursion. With n = 10⁵ a recursive DFS on a long path can overflow the
  stack. See `solutions/cses/planets-and-kingdoms/sol.cpp`.
- Tarjan's algorithm does it in one DFS with low-links. Either is fine; know one well.

## 2. Using the condensation

Many problems become "DP on the DAG of SCCs" (Day 19): *Coin Collector* (each SCC is a
super-node whose value is the sum of its coins, then longest path in the DAG). *Flight
Routes Check* is the special case "is there exactly one SCC?", which you can answer with
two searches from node 1 (forward and reversed) instead of a full SCC computation.

## 3. 2-SAT

Number the literals so negation is cheap: x ↦ 2x, ¬x ↦ 2x + 1, and `lit ^ 1` negates.
For each clause (a ∨ b) add the edges ¬a → b and ¬b → a, then:

- If comp[x] = comp[¬x] for some x: **unsatisfiable**.
- Otherwise set x = true iff comp[x] comes **after** comp[¬x] in topological order. With
  Kosaraju's numbering (sources first) that is `comp[x] > comp[¬x]`. With Tarjan's
  numbering (reverse topological) the comparison flips. Getting this backwards gives
  wrong assignments that still look plausible, so test with a checker.

Why the rule is consistent: if x ⇒ ¬x is reachable, then ¬x is later in topological
order, so the rule sets x false, as it must. Choosing the "later" literal never forces a
path from a true literal to a false one.

Recognising 2-SAT in disguise: every variable is binary (a topping in or out, a switch
up or down, a pipe left or right), and every constraint involves **two** variables. With
three variables per constraint the problem is NP-hard, so look for the two-variable
structure.

## 4. Practice

1. CSES *Planets and Kingdoms* (SCC), *Giant Pizza* (2-SAT), *Flight Routes Check*.
   Reference solutions below. All three accept many outputs, so each has a `check.py`.
2. CSES *Coin Collector* (DP on the condensation), *Strongly Connected Edges* (orient
   every edge so the graph becomes strongly connected; possible iff the graph is
   connected and has no bridge).
3. Stress-test your 2-SAT against a brute force that tries all 2ᵐ assignments for m ≤ 12.
   Include unsatisfiable inputs: the reference tests use (x ∨ x) ∧ (¬x ∨ ¬x).

Reference solutions: `solutions/cses/` (`planets-and-kingdoms`, `giant-pizza`,
`flight-routes-check`).

**Checkpoint:** explain why Kosaraju's first DFS order makes the second pass correct, and
get *Giant Pizza* accepted including an unsatisfiable test you wrote yourself.
