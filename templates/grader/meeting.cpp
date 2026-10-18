// Reference solution for "Meeting point".
// f(p) = sum |x_i - p| is convex and piecewise linear, with slope
// (#houses left of p) - (#houses right of p). The slope changes sign at a median,
// so p = median is optimal. nth_element finds it in O(N) (sorting, O(N log N), is fine too).
#include "meeting.h"
#include <bits/stdc++.h>
using namespace std;

long long min_total_walk(vector<int> x) {
    size_t mid = x.size() / 2;
    nth_element(x.begin(), x.begin() + mid, x.end());
    long long p = x[mid], total = 0;
    for (int xi : x) total += llabs(xi - p);
    return total;
}
