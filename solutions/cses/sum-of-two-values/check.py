import sys

n, x, *a = map(int, open(sys.argv[1]).read().split())
out = open(sys.argv[2]).read().split()
possible = any(a[i] + a[j] == x for i in range(n) for j in range(i + 1, n))
if out == ["IMPOSSIBLE"]:
    sys.exit(1 if possible else 0)
ok = (len(out) == 2 and all(s.isdigit() for s in out))
if ok:
    i, j = int(out[0]), int(out[1])
    ok = i != j and 1 <= i <= n and 1 <= j <= n and a[i - 1] + a[j - 1] == x
sys.exit(0 if ok else 1)
