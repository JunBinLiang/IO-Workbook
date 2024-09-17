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

const int MOD = 1e9 + 7;
using ll = long long;
ll modInverse(ll a, ll m) {
    ll m0 = m;
    ll y = 0, x = 1;
    if (m == 1)
        return 0;
    while (a > 1) {
          // q is quotient
        ll q = a / m;
        ll t = m;
        // m is remainder now, process
        // same as Euclid's algo
        m = a % m;
        a = t;
        t = y;
        // Update x and y
        y = x - q * y;
        x = t;
    }
    // Make x positive
    if (x < 0)
        x += m0;
    return x;
}


void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    long long s = 0;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        s += a[i];
        s %= MOD;
    }

    long long y = (n + 0ll) * (n - 1) / 2;
    y %= MOD;
    y = modInverse(y, MOD);
    long long x = 0;
    for(int i = 0; i < n; i++) {
        x += (a[i] + 0ll) * ((s - a[i] + MOD) % MOD);
        x %= MOD;
    }
    x *= modInverse(2, MOD);
    x %= MOD;
    cout << (x * y) % MOD << endl;
}     

int main() {
    int t = 1;
    std :: cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
