"""Random input for the maximum-subarray-sum example: n, then n integers."""
import random
import sys

random.seed(int(sys.argv[1]))
n = random.randint(1, 8)
print(n)
print(*(random.randint(-10, 10) for _ in range(n)))
