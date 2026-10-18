// Sample grader for the task "Meeting point".
// Like an IOI grader, it reads the input, calls YOUR function, and prints the result.
// The official grader may be different, so never rely on its internals.
// Input:  N, then x[0] ... x[N-1].   Output: min_total_walk(x).
#include <cstdio>
#include <vector>
#include "meeting.h"

int main() {
    int n;
    if (std::scanf("%d", &n) != 1) return 1;
    std::vector<int> x(n);
    for (int i = 0; i < n; i++)
        if (std::scanf("%d", &x[i]) != 1) return 1;
    std::printf("%lld\n", min_total_walk(x));
    return 0;
}
