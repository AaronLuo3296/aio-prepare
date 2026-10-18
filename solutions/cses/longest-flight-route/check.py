import sys

inp = open(sys.argv[1]).read().split()
out = open(sys.argv[2]).read().split()
n, m = int(inp[0]), int(inp[1])
edges = [(int(inp[2 + 2 * i]), int(inp[3 + 2 * i])) for i in range(m)]
adj = {v: [] for v in range(1, n + 1)}
for a, b in edges:
    adj[a].append(b)


def longest(u):  # most cities on a path u -> n, or 0 if n is unreachable (DAG: plain recursion)
    if u == n:
        return 1
    best = max((longest(v) for v in adj[u]), default=0)
    return best + 1 if best else 0


best = longest(1)
if best == 0:
    sys.exit(0 if out == ["IMPOSSIBLE"] else 1)
try:
    route = list(map(int, out))
except ValueError:
    sys.exit(1)
k, route = route[0], route[1:]
ok = (len(route) == k == best and route[0] == 1 and route[-1] == n
      and all(route[i + 1] in adj[route[i]] for i in range(k - 1)))
sys.exit(0 if ok else 1)
