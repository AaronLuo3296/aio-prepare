// CSES: Police Chase
// Max-flow min-cut. Give every street capacity 1 in both directions; the maximum flow from
// 1 to n equals the minimum number of streets to close. After the flow, the nodes still
// reachable from 1 in the residual network form the source side S of a minimum cut; the
// streets with exactly one end in S are the answer. Dinic: O(V^2 E), tiny here.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Dinic {
    struct Edge { int to; ll cap; };
    vector<Edge> e;                         // edge i and i^1 are each other's reverse
    vector<vector<int>> g;
    vector<int> level, it;
    Dinic(int n) : g(n + 1), level(n + 1), it(n + 1) {}
    void add_edge(int a, int b, ll c, ll rc = 0) {
        g[a].push_back(e.size()), e.push_back({b, c});
        g[b].push_back(e.size()), e.push_back({a, rc});
    }
    bool bfs(int s, int t) {                // level graph of the residual network
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        q.push(s), level[s] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int id : g[u])
                if (e[id].cap > 0 && level[e[id].to] < 0) level[e[id].to] = level[u] + 1, q.push(e[id].to);
        }
        return level[t] >= 0;
    }
    ll dfs(int u, int t, ll f) {            // one augmenting path along increasing levels
        if (u == t) return f;
        for (int &i = it[u]; i < (int)g[u].size(); i++) {
            Edge &x = e[g[u][i]];
            if (x.cap > 0 && level[x.to] == level[u] + 1) {
                ll got = dfs(x.to, t, min(f, x.cap));
                if (got > 0) {
                    x.cap -= got, e[g[u][i] ^ 1].cap += got;
                    return got;
                }
            }
        }
        return 0;
    }
    ll max_flow(int s, int t) {
        ll flow = 0;
        while (bfs(s, t)) {
            fill(it.begin(), it.end(), 0);
            while (ll f = dfs(s, t, LLONG_MAX)) flow += f;
        }
        return flow;
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    Dinic d(n);
    vector<pair<int, int>> streets(m);
    for (auto &[a, b] : streets) cin >> a >> b, d.add_edge(a, b, 1, 1);
    cout << d.max_flow(1, n) << "\n";
    d.bfs(1, n);                            // level >= 0  <=>  reachable in the residual graph
    for (auto [a, b] : streets)
        if ((d.level[a] >= 0) != (d.level[b] >= 0)) cout << a << " " << b << "\n";
}
