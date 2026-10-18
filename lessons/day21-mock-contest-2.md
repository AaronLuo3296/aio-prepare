# Day 21: Mock contest #2

**Goal:** a full Senior-level AIO paper under contest conditions, then measure progress
against mock #1.
**Math bridge:** as in olympiad training, the score matters less than the post-mortem.
Track which *kinds* of mistakes are disappearing.

---

## 1. Setup

- Choose a **Senior**-level year from [ORAC AIO Sets](https://orac2.info/hub/aio/) that you
  have not seen. Check the current year's rules for the real duration; use 3 hours if unsure.
- Use the same routine as [Day 14](day14-mock-contest-1.md): 15 minutes reading every
  problem and writing down N's bound, then bank subtasks, then go deep on one problem.

## 2. Graph-specific checklist (Week 3 bugs)

Before submitting a graph solution, check:

- [ ] Vertices numbered 1..N: arrays sized N + 1.
- [ ] Undirected edge stored in **both** directions; directed edge in one.
- [ ] Graph may be **disconnected**: loop over all start vertices.
- [ ] Grid BFS: bounds checked **before** indexing; visited marked when **pushing**, not
      when popping (otherwise a cell enters the queue many times).
- [ ] Dijkstra: min-heap, stale-entry check, `long long` distances.
- [ ] Deep recursion on a path graph of 10⁵ vertices: use BFS order or an explicit stack.

## 3. After the contest

1. Record the score per subtask next to mock #1's.
2. Upsolve everything, reading ORAC's official solutions where available.
3. Compare error-log categories with mock #1: which shrank, which grew?
4. If a graph problem was missed, write down which model you failed to see (grid as graph,
   state-expanded graph, DAG of states, tree DP). Recognising the model is the hard part.

**Checkpoint:** a two-column comparison of mock #1 and mock #2 (score, top error
categories), and every problem upsolved.
