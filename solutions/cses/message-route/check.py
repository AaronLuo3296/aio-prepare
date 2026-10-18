import sys

inp = open(sys.argv[1]).read().split()
out = open(sys.argv[2]).read().split()
n, m = int(inp[0]), int(inp[1])
edges = [(int(inp[2 + 2 * i]), int(inp[3 + 2 * i])) for i in range(m)]
from collections import deque

adj = {v: set() for v in range(1, n + 1)}
for a, b in edges:
    adj[a].add(b)
    adj[b].add(a)
dist = {1: 0}
q = deque([1])
while q:
    u = q.popleft()
    for v in adj[u]:
        if v not in dist:
            dist[v] = dist[u] + 1
            q.append(v)
if n not in dist:
    sys.exit(0 if out == ["IMPOSSIBLE"] else 1)
try:
    route = list(map(int, out))
except ValueError:
    sys.exit(1)
k, route = route[0], route[1:]
ok = (len(route) == k == dist[n] + 1 and route[0] == 1 and route[-1] == n
      and all(route[i + 1] in adj[route[i]] for i in range(k - 1)))
sys.exit(0 if ok else 1)
