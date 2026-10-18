// CSES: Permutations
// All evens then all odds: neighbours inside each block differ by 2, and the junction
// (largest even, 1) differs by >= 3 once n >= 4. n = 2, 3 are impossible (check by hand).
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n;
    cin >> n;
    if (n == 2 || n == 3) {
        cout << "NO SOLUTION\n";
        return 0;
    }
    for (int i = 2; i <= n; i += 2) cout << i << " ";
    for (int i = 1; i <= n; i += 2) cout << i << " ";
    cout << "\n";
}
