import sys

t = list(map(int, open(sys.argv[1]).read().split()))
out = open(sys.argv[2]).read().split()
k_expected = int(open(sys.argv[3]).read().split()[0])
n, m = t[0], t[1]
edges = {frozenset((t[2 + 2 * i], t[3 + 2 * i])) for i in range(m)}
try:
    vals = list(map(int, out))
except ValueError:
    sys.exit(1)
if not vals or vals[0] != k_expected or len(vals) != 1 + 2 * k_expected:
    sys.exit(1)
closed = {frozenset(vals[1 + 2 * i:3 + 2 * i]) for i in range(k_expected)}
if len(closed) != k_expected or not closed <= edges:
    sys.exit(1)
adj = {v: [] for v in range(1, n + 1)}
for e in edges - closed:
    a, b = tuple(e)
    adj[a].append(b)
    adj[b].append(a)
seen, st = {1}, [1]
while st:
    u = st.pop()
    for v in adj[u]:
        if v not in seen:
            seen.add(v)
            st.append(v)
sys.exit(0 if n not in seen else 1)
