import sys

out = list(open(sys.argv[2]).read().split())
exp = list(open(sys.argv[3]).read().split())


def points(tokens):
    k = int(tokens[0])
    if len(tokens) != 1 + 2 * k:
        raise ValueError
    return k, sorted(zip(tokens[1::2], tokens[2::2]))


try:
    ok = points(out) == points(exp)
except (ValueError, IndexError):
    ok = False
sys.exit(0 if ok else 1)
