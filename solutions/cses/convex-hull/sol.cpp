// CSES: Convex Hull
// Andrew's monotone chain. Sort points by (x, y); build the lower hull left to right and
// the upper hull right to left, popping the last point while it makes a RIGHT turn
// (cross < 0). Popping only on strict right turns keeps collinear boundary points, which
// this problem asks for. O(n log n).
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
struct P { ll x, y; };
// Cross product of (a - o) and (b - o): > 0 if o -> a -> b turns left. With coordinates
// up to 10^9 the differences are up to 2*10^9, so each product is up to 4*10^18 and the
// result fits in long long (max about 9.2*10^18).
ll cross(P o, P a, P b) { return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x); }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<P> p(n);
    for (auto &q : p) cin >> q.x >> q.y;
    sort(p.begin(), p.end(), [](P a, P b) { return a.x != b.x ? a.x < b.x : a.y < b.y; });
    vector<P> hull;
    for (int pass = 0; pass < 2; pass++) {
        size_t start = hull.size();
        for (P q : p) {
            while (hull.size() >= start + 2 && cross(hull[hull.size() - 2], hull.back(), q) < 0)
                hull.pop_back();
            hull.push_back(q);
        }
        hull.pop_back();                    // the last point starts the other chain
        reverse(p.begin(), p.end());
    }
    cout << hull.size() << "\n";
    for (P q : hull) cout << q.x << " " << q.y << "\n";
}
