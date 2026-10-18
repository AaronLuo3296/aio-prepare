import sys

n = int(open(sys.argv[1]).read())
nums = list(map(int, open(sys.argv[2]).read().split()))
k = nums[0]
if k != 2 ** n - 1 or len(nums) != 1 + 2 * k:
    sys.exit(1)
stacks = {1: list(range(n, 0, -1)), 2: [], 3: []}
for i in range(k):
    a, b = nums[1 + 2 * i], nums[2 + 2 * i]
    if a not in stacks or b not in stacks or not stacks[a]:
        sys.exit(1)
    if stacks[b] and stacks[b][-1] < stacks[a][-1]:
        sys.exit(1)
    stacks[b].append(stacks[a].pop())
sys.exit(0 if stacks[3] == list(range(n, 0, -1)) else 1)
