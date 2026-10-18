// CSES: Point Location Test
// The sign of the cross product (p2 - p1) x (p3 - p1) says on which side of the directed
// line p1 -> p2 the point p3 lies: positive = left, negative = right, zero = on the line.
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
    int t;
    cin >> t;
    while (t--) {
        P a, b, c;
        cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;
        ll v = cross(a, b, c);
        cout << (v > 0 ? "LEFT" : v < 0 ? "RIGHT" : "TOUCH") << "\n";
    }
}
