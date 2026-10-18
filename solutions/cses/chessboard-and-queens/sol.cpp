// CSES: Chessboard and Queens
// Backtracking row by row, tracking used columns and both diagonal directions
// (r + c and r - c + 7 are constant along diagonals).
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

array<string, 8> board;
array<bool, 8> col{};
array<bool, 15> diag1{}, diag2{};

int place(int r) {
    if (r == 8) return 1;
    int ways = 0;
    for (int c = 0; c < 8; c++) {
        if (board[r][c] == '*' || col[c] || diag1[r + c] || diag2[r - c + 7]) continue;
        col[c] = diag1[r + c] = diag2[r - c + 7] = true;
        ways += place(r + 1);
        col[c] = diag1[r + c] = diag2[r - c + 7] = false;
    }
    return ways;
}

int main() {
    for (auto& row : board) cin >> row;
    cout << place(0) << "\n";
}
