// CSES: Nearest Smaller Values
// Monotonic stack of positions whose values increase from bottom to top. Before pushing i,
// pop every j with x[j] >= x[i]: such a j can never be the answer for i or anything right
// of i, because i is closer and no larger. Each index is pushed and popped once: O(n).
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> x(n + 1), st;               // st holds 1-based positions
    for (int i = 1; i <= n; i++) {
        cin >> x[i];
        while (!st.empty() && x[st.back()] >= x[i]) st.pop_back();
        cout << (st.empty() ? 0 : st.back()) << " \n"[i == n];
        st.push_back(i);
    }
}
