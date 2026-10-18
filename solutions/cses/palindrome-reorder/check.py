import sys
from collections import Counter

s = open(sys.argv[1]).read().strip()
out = open(sys.argv[2]).read().split()
possible = sum(v % 2 for v in Counter(s).values()) <= 1
if not possible:
    sys.exit(0 if out == ["NO", "SOLUTION"] else 1)
ok = len(out) == 1 and out[0] == out[0][::-1] and Counter(out[0]) == Counter(s)
sys.exit(0 if ok else 1)
