// CSES: Line Segment Intersection
// Segments AB and CD cross properly iff C and D are strictly on opposite sides of line AB
// and A and B strictly on opposite sides of line CD (signs of four cross products).
// Otherwise they meet only if an endpoint lies ON the other segment: collinear (cross = 0)
// and inside its bounding box. This also covers overlapping collinear segments.
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
struct P { ll x, y; };
// Cross product of (a - o) and (b - o): > 0 if o -> a -> b turns left. With coordinates
// up to 10^9 the differences are up to 2*10^9, so each product is up to 4*10^18 and the
// result fits in long long (max about 9.2*10^18).
ll cross(P o, P a, P b) { return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x); }

int sgn(ll v) { return (v > 0) - (v < 0); }
bool on_segment(P a, P b, P p) {            // assumes p is collinear with a, b
    return min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) && min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        P a, b, c, d;
        cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y >> d.x >> d.y;
        int s1 = sgn(cross(a, b, c)), s2 = sgn(cross(a, b, d));
        int s3 = sgn(cross(c, d, a)), s4 = sgn(cross(c, d, b));
        bool yes = s1 * s2 < 0 && s3 * s4 < 0;
        yes = yes || (s1 == 0 && on_segment(a, b, c)) || (s2 == 0 && on_segment(a, b, d));
        yes = yes || (s3 == 0 && on_segment(c, d, a)) || (s4 == 0 && on_segment(c, d, b));
        cout << (yes ? "YES" : "NO") << "\n";
    }
}
