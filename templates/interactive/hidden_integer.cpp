// CSES: Hidden Integer (interactive)
// Binary search on [lo, hi], which always contains x. "? mid" answers whether mid < x:
// YES -> x in [mid+1, hi], NO -> x in [lo, mid]. Each question halves the interval, and
// 2^30 > 10^9, so 30 questions suffice. Flush after every line, or the grader never sees it.
#include <bits/stdc++.h>
using namespace std;
int main() {
    int lo = 1, hi = 1000000000;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        cout << "? " << mid << endl;        // endl flushes
        string reply;
        cin >> reply;
        if (reply == "YES") lo = mid + 1;
        else hi = mid;
    }
    cout << "! " << lo << endl;
}
