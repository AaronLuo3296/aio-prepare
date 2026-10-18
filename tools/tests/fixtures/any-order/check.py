import sys

n = int(open(sys.argv[1]).read())
got = sorted(map(int, open(sys.argv[2]).read().split()))
sys.exit(0 if got == list(range(1, n + 1)) else 1)
