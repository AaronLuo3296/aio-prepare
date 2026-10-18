// CSES: Sum of Two Values
// Scan left to right remembering where each value was seen. When x - a[i] was seen
// earlier, done. O(n log n). (Sort + two pointers is the other classic solution.)
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, x;
    cin >> n >> x;
    map<int, int> where;                 // value -> 1-based position
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        auto it = where.find(x - a);
        if (it != where.end()) {
            cout << it->second << " " << i << "\n";
            return 0;
        }
        where[a] = i;
    }
    cout << "IMPOSSIBLE\n";
}
