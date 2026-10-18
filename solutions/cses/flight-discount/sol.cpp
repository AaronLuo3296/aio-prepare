// CSES: Flight Discount
// State-expanded graph: (city, coupon used?). From (u,0) a flight goes to (v,0) at full
// price or to (v,1) at half price; from (u,1) only full price. Dijkstra on 2n states.
// O((n + m) log m).
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, ll>>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        ll c;
        cin >> a >> b >> c;
        adj[a].push_back({b, c});
    }

    vector<array<ll, 2>> dist(n + 1, {LLONG_MAX, LLONG_MAX});
    priority_queue<tuple<ll, int, int>, vector<tuple<ll, int, int>>, greater<>> pq;
    dist[1][0] = 0;
    pq.push({0, 1, 0});
    while (!pq.empty()) {
        auto [d, u, used] = pq.top();
        pq.pop();
        if (d > dist[u][used]) continue;
        for (auto [v, w] : adj[u]) {
            if (d + w < dist[v][used]) {
                dist[v][used] = d + w;
                pq.push({dist[v][used], v, used});
            }
            if (!used && d + w / 2 < dist[v][1]) {
                dist[v][1] = d + w / 2;
                pq.push({dist[v][1], v, 1});
            }
        }
    }
    cout << min(dist[n][0], dist[n][1]) << "\n";
}
