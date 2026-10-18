import sys

inp = list(map(int, open(sys.argv[1]).read().split()))
out = open(sys.argv[2]).read().split()
k_expected = int(open(sys.argv[3]).read().split()[0])
n, m = inp[0], inp[1]
adj = {v: [] for v in range(1, n + 1)}
for i in range(m):
    adj[inp[2 + 2 * i]].append(inp[3 + 2 * i])
reach = {}
for s in range(1, n + 1):
    seen, st = {s}, [s]
    while st:
        u = st.pop()
        for v in adj[u]:
            if v not in seen:
                seen.add(v)
                st.append(v)
    reach[s] = seen
try:
    vals = list(map(int, out))
except ValueError:
    sys.exit(1)
if len(vals) != n + 1 or vals[0] != k_expected:
    sys.exit(1)
k, lab = vals[0], [0] + vals[1:]
ok = set(lab[1:]) == set(range(1, k + 1))
ok = ok and all((lab[a] == lab[b]) == (b in reach[a] and a in reach[b])
                for a in range(1, n + 1) for b in range(1, n + 1))
sys.exit(0 if ok else 1)
