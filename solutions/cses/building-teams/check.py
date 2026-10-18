import sys

inp = open(sys.argv[1]).read().split()
out = open(sys.argv[2]).read().split()
n, m = int(inp[0]), int(inp[1])
edges = [(int(inp[2 + 2 * i]), int(inp[3 + 2 * i])) for i in range(m)]
import itertools

possible = any(all(c[a - 1] != c[b - 1] for a, b in edges)
               for c in itertools.product((1, 2), repeat=n))
if not possible:
    sys.exit(0 if out == ["IMPOSSIBLE"] else 1)
ok = (len(out) == n and all(t in ("1", "2") for t in out)
      and all(out[a - 1] != out[b - 1] for a, b in edges))
sys.exit(0 if ok else 1)
