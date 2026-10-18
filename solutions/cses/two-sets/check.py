import sys

n = int(open(sys.argv[1]).read())
out = open(sys.argv[2]).read().split()
if n * (n + 1) // 2 % 2 == 1:
    sys.exit(0 if out == ["NO"] else 1)
if out[0] != "YES":
    sys.exit(1)
nums = list(map(int, out[1:]))
k = nums[0]
a = nums[1:1 + k]
m = nums[1 + k]
b = nums[2 + k:2 + k + m]
ok = (len(nums) == 2 + k + m and sorted(a + b) == list(range(1, n + 1))
      and sum(a) == sum(b))
sys.exit(0 if ok else 1)
