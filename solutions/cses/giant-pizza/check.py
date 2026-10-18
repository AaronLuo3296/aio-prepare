import sys

t = open(sys.argv[1]).read().split()
out = open(sys.argv[2]).read().split()
expected = open(sys.argv[3]).read().split()
n, m = int(t[0]), int(t[1])
if expected == ["IMPOSSIBLE"]:
    sys.exit(0 if out == ["IMPOSSIBLE"] else 1)
choice = "".join(out)
if len(choice) != m or set(choice) - set("+-"):
    sys.exit(1)
for i in range(n):
    a, x, b, y = t[2 + 4 * i], int(t[3 + 4 * i]), t[4 + 4 * i], int(t[5 + 4 * i])
    if choice[x - 1] != a and choice[y - 1] != b:
        sys.exit(1)
sys.exit(0)
