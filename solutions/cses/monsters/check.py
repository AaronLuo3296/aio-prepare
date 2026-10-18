import sys

inp = open(sys.argv[1]).read().split()
out = open(sys.argv[2]).read().split()
from collections import deque

n, m = int(inp[0]), int(inp[1])
g = inp[2:2 + n]
STEP = {"U": (-1, 0), "D": (1, 0), "L": (0, -1), "R": (0, 1)}


def find(ch):
    return [(r, c) for r in range(n) for c in range(m) if g[r][c] == ch]


def bfs(sources, allowed=lambda cell, d: True):
    dist = {s: 0 for s in sources}
    q = deque(sources)
    while q:
        r, c = q.popleft()
        for dr, dc in STEP.values():
            nb = (r + dr, c + dc)
            if (0 <= nb[0] < n and 0 <= nb[1] < m and g[nb[0]][nb[1]] != "#"
                    and nb not in dist and allowed(nb, dist[(r, c)] + 1)):
                dist[nb] = dist[(r, c)] + 1
                q.append(nb)
    return dist


def walk(start, path):
    """Cells visited after each move, or None if the path hits a wall or leaves the grid."""
    cells, (r, c) = [], start
    for ch in path:
        if ch not in STEP:
            return None
        r, c = r + STEP[ch][0], c + STEP[ch][1]
        if not (0 <= r < n and 0 <= c < m) or g[r][c] == "#":
            return None
        cells.append((r, c))
    return cells

a = find("A")[0]
mon = bfs(find("M"))
INF = float("inf")
mine = bfs([a], lambda cell, d: d < mon.get(cell, INF))


def border(cell):
    return cell[0] in (0, n - 1) or cell[1] in (0, m - 1)


if not any(border(cell) for cell in mine):
    sys.exit(0 if out == ["NO"] else 1)
if out[:1] != ["YES"] or len(out) not in (2, 3):
    sys.exit(1)
path = out[2] if len(out) == 3 else ""
if out[1] != str(len(path)):
    sys.exit(1)
cells = walk(a, path)
ok = (cells is not None and border(cells[-1] if cells else a)
      and all(t < mon.get(cell, INF) for t, cell in enumerate(cells, 1)))
sys.exit(0 if ok else 1)
