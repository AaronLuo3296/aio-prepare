// CSES: Creating Strings
// Sort, then next_permutation walks the distinct permutations in lexicographic order.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    string s;
    cin >> s;
    sort(s.begin(), s.end());
    vector<string> all;
    do {
        all.push_back(s);
    } while (next_permutation(s.begin(), s.end()));

    cout << all.size() << "\n";
    for (const string& t : all) cout << t << "\n";
}
