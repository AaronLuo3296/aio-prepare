// CSES: Shortest Routes I
// Dijkstra with a min-priority queue. Skip stale queue entries (d > dist[u]).
// Paths can reach 1e5 * 1e9, so long long. O((n + m) log m).
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

    vector<ll> dist(n + 1, LLONG_MAX);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
    dist[1] = 0;
    pq.push({0, 1});
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : adj[u])
            if (d + w < dist[v]) {
                dist[v] = d + w;
                pq.push({dist[v], v});
            }
    }
    for (int i = 1; i <= n; i++) cout << dist[i] << " ";
    cout << "\n";
}
