#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
#include<unordered_set>
#include<map>
#include<string>
#include <string.h>
#include <bitset>
#include <queue>

using namespace std;


void solve() {
    int n, m, k, t;
    cin >> n >> m >> k >> t;
    vector<int> a(t);
    for(int i = 0; i < t; i++) {
        cin >> a[i];
    }

    sort(a.begin(), a.end());
    reverse(a.begin(), a.end());
    vector<long long> b;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) { //how many time is cover
            int l1 = max(0, i - k + 1); int l2 = min(i, n - k);
            int l3 = max(0, j - k + 1); int l4 = min(j, m - k);
            int h = max(0, l2 - l1 + 1);
            int w = max(0, l4 - l3 + 1);
            b.push_back((h + 0ll) * w);
        }
    }

    sort(b.begin(), b.end());
    reverse(b.begin(), b.end());

    long long ans = 0;
    for(int i = 0; i < a.size(); i++) {
        ans += ((a[i] + 0ll) * b[i]);
    }
    cout << ans << endl;
}    

int main() {
    int t = 1;
    std :: cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
