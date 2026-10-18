import sys

inp = open(sys.argv[1]).read().split()
out = open(sys.argv[2]).read().split()
n, m = int(inp[0]), int(inp[1])
edges = [(int(inp[2 + 2 * i]), int(inp[3 + 2 * i])) for i in range(m)]
parent = list(range(n + 1))


def find(x):
    while parent[x] != x:
        x = parent[x]
    return x


has_cycle = False
for a, b in edges:
    if find(a) == find(b):
        has_cycle = True
    parent[find(a)] = find(b)
if not has_cycle:
    sys.exit(0 if out == ["IMPOSSIBLE"] else 1)
try:
    route = list(map(int, out))
except ValueError:
    sys.exit(1)
k, route = route[0], route[1:]
es = {frozenset(e) for e in edges}
ok = (len(route) == k >= 4 and route[0] == route[-1]
      and len(set(route[:-1])) == k - 1
      and all(frozenset((route[i], route[i + 1])) in es for i in range(k - 1)))
sys.exit(0 if ok else 1)
