#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include <string.h>

using namespace std;
using ll = long long;

void solve() {
    int k, n;
    cin >> k >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];

    sort(a.begin(), a.end());
    long long ans = 0;
    for(int i = 0; i < n - 1; i++) {
        ans += a[i];
        ans += a[i] - 1;
    }
    cout << ans << endl;
}    

int main() {
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
