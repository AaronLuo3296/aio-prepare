import sys

inp = list(map(int, open(sys.argv[1]).read().split()))
out = open(sys.argv[2]).read().split()
expected = open(sys.argv[3]).read().split()[0]
n, m = inp[0], inp[1]
w = {}
for i in range(m):
    a, b, c = inp[2 + 3 * i:5 + 3 * i]
    w[(a, b)] = min(w.get((a, b), c), c)
if not out or out[0] != expected:
    sys.exit(1)
if expected == "NO":
    sys.exit(0 if out == ["NO"] else 1)
try:
    cyc = list(map(int, out[1:]))
except ValueError:
    sys.exit(1)
ok = len(cyc) >= 2 and cyc[0] == cyc[-1] and all((a, b) in w for a, b in zip(cyc, cyc[1:]))
ok = ok and sum(w[(a, b)] for a, b in zip(cyc, cyc[1:])) < 0
sys.exit(0 if ok else 1)
