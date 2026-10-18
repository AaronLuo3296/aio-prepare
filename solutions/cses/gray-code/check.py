import sys

n = int(open(sys.argv[1]).read())
codes = open(sys.argv[2]).read().split()
ok = (len(codes) == 2 ** n and len(set(codes)) == len(codes)
      and all(len(c) == n and set(c) <= {"0", "1"} for c in codes)
      and all(sum(x != y for x, y in zip(c, d)) == 1 for c, d in zip(codes, codes[1:])))
sys.exit(0 if ok else 1)
