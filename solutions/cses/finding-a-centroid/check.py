import sys

t = list(map(int, open(sys.argv[1]).read().split()))
out = open(sys.argv[2]).read().split()
n = t[0]
adj = {v: [] for v in range(1, n + 1)}
for i in range(n - 1):
    a, b = t[1 + 2 * i], t[2 + 2 * i]
    adj[a].append(b)
    adj[b].append(a)
if len(out) != 1 or not out[0].isdigit() or not 1 <= int(out[0]) <= n:
    sys.exit(1)
c = int(out[0])
for v in adj[c]:
    seen, st = {c, v}, [v]
    while st:
        u = st.pop()
        for w in adj[u]:
            if w not in seen:
                seen.add(w)
                st.append(w)
    if len(seen) - 1 > n // 2:
        sys.exit(1)
sys.exit(0)
