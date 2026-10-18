import sys

t = list(map(int, open(sys.argv[1]).read().split()))
out = open(sys.argv[2]).read().split()
r_expected = int(open(sys.argv[3]).read().split()[0])
n, m, k = t[0], t[1], t[2]
allowed = {(t[3 + 2 * i], t[4 + 2 * i]) for i in range(k)}
try:
    vals = list(map(int, out))
except ValueError:
    sys.exit(1)
if not vals or vals[0] != r_expected or len(vals) != 1 + 2 * r_expected:
    sys.exit(1)
pairs = [tuple(vals[1 + 2 * i:3 + 2 * i]) for i in range(r_expected)]
ok = all(p in allowed for p in pairs)
ok = ok and len({a for a, _ in pairs}) == r_expected and len({b for _, b in pairs}) == r_expected
sys.exit(0 if ok else 1)
