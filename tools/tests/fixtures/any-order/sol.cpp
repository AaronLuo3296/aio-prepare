// Prints 1..n in descending order; the checker accepts any permutation.
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin >> n;
    for (int i = n; i >= 1; i--) cout << i << " \n"[i == 1];
}
