import sys

inp = open(sys.argv[1]).read().split()
out = open(sys.argv[2]).read().split()
n, m = int(inp[0]), int(inp[1])
edges = [(int(inp[2 + 2 * i]), int(inp[3 + 2 * i])) for i in range(m)]
import itertools

possible = any(all(p.index(a) < p.index(b) for a, b in edges)
               for p in itertools.permutations(range(1, n + 1)))
if not possible:
    sys.exit(0 if out == ["IMPOSSIBLE"] else 1)
try:
    order = list(map(int, out))
except ValueError:
    sys.exit(1)
ok = sorted(order) == list(range(1, n + 1))
ok = ok and all(order.index(a) < order.index(b) for a, b in edges)
sys.exit(0 if ok else 1)
