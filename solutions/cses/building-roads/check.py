import sys

inp = open(sys.argv[1]).read().split()
out = open(sys.argv[2]).read().split()
n, m = int(inp[0]), int(inp[1])
edges = [(int(inp[2 + 2 * i]), int(inp[3 + 2 * i])) for i in range(m)]


def count_components(es):
    parent = list(range(n + 1))

    def find(x):
        while parent[x] != x:
            x = parent[x]
        return x

    for a, b in es:
        parent[find(a)] = find(b)
    return len({find(v) for v in range(1, n + 1)})


try:
    k = int(out[0])
    new = [(int(out[1 + 2 * i]), int(out[2 + 2 * i])) for i in range(k)]
except (IndexError, ValueError):
    sys.exit(1)
ok = (len(out) == 1 + 2 * k and k == count_components(edges) - 1
      and all(1 <= a <= n and 1 <= b <= n for a, b in new)
      and count_components(edges + new) == 1)
sys.exit(0 if ok else 1)
