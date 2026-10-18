// CSES: Tower of Hanoi
// Move n-1 disks to the spare stack, the largest to the target, then n-1 on top.
// Moves satisfy m(n) = 2 m(n-1) + 1, so m(n) = 2^n - 1 (induction).
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<pair<int, int>> moves;

void solve(int n, int from, int to, int spare) {
    if (n == 0) return;
    solve(n - 1, from, spare, to);
    moves.push_back({from, to});
    solve(n - 1, spare, to, from);
}

int main() {
    int n;
    cin >> n;
    solve(n, 1, 3, 2);
    cout << moves.size() << "\n";
    for (auto [a, b] : moves) cout << a << " " << b << "\n";
}
