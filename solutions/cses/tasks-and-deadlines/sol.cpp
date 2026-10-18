// CSES: Tasks and Deadlines
// Total reward = sum d_i - sum f_i. The deadlines are fixed, so minimise the sum of
// finishing times: shortest task first (swap any adjacent inversion to improve). O(n log n).
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<ll> duration(n);
    ll reward = 0;
    for (int i = 0; i < n; i++) {
        ll d;
        cin >> duration[i] >> d;
        reward += d;
    }
    sort(duration.begin(), duration.end());
    ll now = 0;
    for (ll a : duration) {
        now += a;
        reward -= now;
    }
    cout << reward << "\n";
}
