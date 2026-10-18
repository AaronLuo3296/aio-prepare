import sys

inp = list(map(int, open(sys.argv[1]).read().split()))
out = open(sys.argv[2]).read().split()
expected = open(sys.argv[3]).read().split()[0]
n, m = inp[0], inp[1]
adj = {v: [] for v in range(1, n + 1)}
for i in range(m):
    adj[inp[2 + 2 * i]].append(inp[3 + 2 * i])
if not out or out[0] != expected:
    sys.exit(1)
if expected == "YES":
    sys.exit(0 if out == ["YES"] else 1)
try:
    a, b = map(int, out[1:])
except ValueError:
    sys.exit(1)
if not (1 <= a <= n and 1 <= b <= n):
    sys.exit(1)
seen, st = {a}, [a]
while st:
    u = st.pop()
    for v in adj[u]:
        if v not in seen:
            seen.add(v)
            st.append(v)
sys.exit(0 if b not in seen else 1)
