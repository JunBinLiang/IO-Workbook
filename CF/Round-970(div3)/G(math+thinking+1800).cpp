#include<iostream>
#include<algorithm>
#include<vector>
#include<unordered_set>
#include<set>
#include<unordered_map>
#include<map>
#include<string>
#include <string.h>
#include <bitset>
#include <queue>
#include <cmath>

using namespace std;


//12:35
void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    if(n == 1) {
        int ans = k - 1;
        if(a[0] <= ans) ans++;
        cout << ans << endl;
        return;
    }

    int g = a[0];
    for(int i = 0; i < n; i++) {
        g = __gcd(g, a[i]);
    }

    if(g == 1) {
        cout << n + k - 1 << endl;
        return;
    }

    //0 4 8 12 16
    for(int i = 1; i < n; i++) {
        int diff = g - 1;
        if(k <= diff) {
            cout << (i - 1ll) * g + k << endl;
            return;
        } else {
            k -= diff;
        }
    }
    cout << (g + 0ll) * (n - 1) + k << endl;
}     

int main() {
    int t = 1;
    std :: cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
