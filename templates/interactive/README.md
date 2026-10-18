# Interactive tasks: local testing

In an interactive task your program talks to a judge program (the **interactor**) instead
of reading a fixed input file. You print a question, flush, read the answer, and repeat.
You cannot test this by piping a file into your program, because the answers depend on
your questions. This folder gives you a local judge.

| File | Purpose |
|------|---------|
| `interact.py` | Wires your program's stdout to the interactor's stdin and back. Prints `ACCEPTED`, `WRONG ANSWER` or `TIMEOUT`. |
| `hidden_integer_interactor.py` | Interactor for CSES *Hidden Integer*: hidden x given on the command line, at most 30 questions. |
| `hidden_integer.cpp` | Reference solution (binary search). **Spoiler.** |

```sh
cd templates/interactive
g++ $(../../tools/cxxflags.sh) hidden_integer.cpp -o hidden_integer
python3 interact.py ./hidden_integer hidden_integer_interactor.py 123456789
python3 interact.py ./hidden_integer hidden_integer_interactor.py 1
python3 interact.py ./hidden_integer hidden_integer_interactor.py 1000000000
```

Always test the extreme hidden values (1 and the maximum). An off-by-one in a binary
search shows up only there.

## Writing your own interactor

Copy `hidden_integer_interactor.py` and change three things: what it reads from the
command line (the hidden data), how it answers a question, and how it checks the final
answer. Exit with code 0 to accept and 1 to reject, and say why on stderr. Use
`print(..., flush=True)` on the interactor side too.

To debug, run your program by hand and type the judge's answers yourself. Print debug
output to `cerr`, never to `cout`, because the interactor reads everything on `cout`.

IOI tasks are usually *function-style* instead (the grader calls your function, see
[`../grader/`](../grader/)). The habit is the same: count your queries, and test the
worst case for the query limit.
