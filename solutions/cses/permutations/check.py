import sys

n = int(open(sys.argv[1]).read())
out = open(sys.argv[2]).read().split()
if n in (2, 3):
    sys.exit(0 if out == ["NO", "SOLUTION"] else 1)
p = list(map(int, out))
ok = sorted(p) == list(range(1, n + 1)) and all(abs(a - b) != 1 for a, b in zip(p, p[1:]))
sys.exit(0 if ok else 1)
