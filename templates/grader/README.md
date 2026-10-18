# IOI-style grader template (Day 26)

At the IOI you do **not** write `main()` and you do **not** read input. You implement one
or more functions with a fixed signature. The judge's *grader* reads the input, calls your
functions, and checks what they return. This folder is a small, complete example of that
format, built around an original toy task.

| File | Role |
|------|------|
| `meeting.h` | The interface: the function signature you must implement. Never edit it. |
| `grader.cpp` | Sample grader: reads input, calls your function, prints the result. |
| `stub.cpp` | Your starting point. Compiles and links, but returns a wrong answer. |
| `meeting.cpp` | Reference solution. Read it only after trying the task. |
| `tests/N.in`, `tests/N.out` | Sample tests (expected outputs from a Python brute force). |

## The task: Meeting point

N friends live at integer positions `x[0..N-1]` on a straight road. They meet at an
integer point p, and each walks to it. Return the minimum possible total walking distance
Σ |x[i] − p|.

```
long long min_total_walk(std::vector<int> x);
```

Constraints: 1 ≤ N ≤ 2·10⁵, |x[i]| ≤ 10⁹ (the answer needs `long long`).

| Subtask | Points | Extra constraint |
|---------|--------|------------------|
| 1 | 30 | N ≤ 1000: try every house as p |
| 2 | 70 | none |

Bank subtask 1 first (O(N²) is 10⁶ steps), then look for the O(N log N) idea. Hint: how
does the total change when p moves one step to the right?

## Compile and run

Compile the grader **together with** your file. There is still exactly one `main`, the
grader's:

```bash
cp stub.cpp meeting.cpp        # only the first time; this overwrites the reference solution
g++ $(../../tools/cxxflags.sh) grader.cpp meeting.cpp -o meeting
./meeting < tests/1.in         # expect the number in tests/1.out
```

(Work in a copy of this folder if you want to keep the reference solution.)
`make test` checks that `meeting.cpp` passes every test and that `stub.cpp` links.

## Rules of the IOI format

- **No `main`** in your file, and no `cin`/`cout` on the real input. Printing to stdout can
  even corrupt the grader's output and get you a wrong answer. Debug with `cerr`.
- **Global variables persist** between calls if the grader calls your function more than
  once. Reset them at the start of each call.
- The **sample grader is not the official one**. It may skip input validation or use a
  different I/O format. Rely only on the task statement.
- Interactive tasks (e.g. IOI 2018 *Combo*) give you a function to *call*, such as
  `press(...)`, declared in the header. The grader counts your calls, and the call limit
  is part of the task.
