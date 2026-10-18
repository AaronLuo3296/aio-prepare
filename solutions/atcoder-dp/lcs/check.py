import sys

s, t = open(sys.argv[1]).read().split()
out = open(sys.argv[2]).read().split()
ans = out[0] if out else ""


def is_subsequence(sub, full):
    it = iter(full)
    return all(ch in it for ch in sub)


L = [[0] * (len(t) + 1) for _ in range(len(s) + 1)]
for i in range(len(s)):
    for j in range(len(t)):
        L[i + 1][j + 1] = L[i][j] + 1 if s[i] == t[j] else max(L[i][j + 1], L[i + 1][j])
ok = (len(out) <= 1 and len(ans) == L[-1][-1]
      and is_subsequence(ans, s) and is_subsequence(ans, t))
sys.exit(0 if ok else 1)
