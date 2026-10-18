// CSES: Removing Digits
// steps[v] = 1 + min over nonzero digits d of v of steps[v - d]; steps[0] = 0. O(n log n).
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin >> n;
    vector<int> steps(n + 1, 0);
    for (int v = 1; v <= n; v++) {
        steps[v] = INT_MAX;
        for (int rest = v; rest > 0; rest /= 10) {
            int d = rest % 10;
            if (d > 0) steps[v] = min(steps[v], steps[v - d] + 1);
        }
    }
    cout << steps[n] << "\n";
}
