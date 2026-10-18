// CSES: School Dance
// Maximum bipartite matching with Kuhn's algorithm: for each boy, search for an augmenting
// path (try a girl; if she is taken, try to re-match her partner elsewhere). Berge: a
// matching is maximum iff no augmenting path exists. O(n * k). Same answer as max flow
// with unit capacities, in fewer lines.
#include <bits/stdc++.h>
using namespace std;
int n, m, k;
vector<vector<int>> adj;
vector<int> match_girl;                     // match_girl[g] = boy matched to g, or 0
vector<bool> visited;

bool try_boy(int b) {
    for (int g : adj[b]) {
        if (visited[g]) continue;
        visited[g] = true;
        if (!match_girl[g] || try_boy(match_girl[g])) return match_girl[g] = b, true;
    }
    return false;
}

int main() {
    cin >> n >> m >> k;
    adj.assign(n + 1, {});
    for (int i = 0; i < k; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
    }
    match_girl.assign(m + 1, 0);
    int r = 0;
    for (int b = 1; b <= n; b++) {
        visited.assign(m + 1, false);
        r += try_boy(b);
    }
    cout << r << "\n";
    for (int g = 1; g <= m; g++)
        if (match_girl[g]) cout << match_girl[g] << " " << g << "\n";
}
