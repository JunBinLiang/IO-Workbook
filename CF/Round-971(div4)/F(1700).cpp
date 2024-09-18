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


//2:27 - 2:41
const int N = 2e5 + 10;
long long s = 0;
int n, m;
long long p[N];

long long get(int l, int r) {
    return p[r] - p[l - 1];
}

long long cal(long long len) {
    if(n == 0) return 0;
    long long shift = len / n;
    long long ans = s * (shift);
    if(len % n != 0) {
        int mod = len % n;
        int l = shift;
        if(n - l >= mod) {
            ans += get(l, l + mod - 1);
        } else {
            ans += get(l, n - 1);
            mod -= (n - l);
            ans += get(0, mod - 1);
        }
    }
    return ans;
}

void solve() {
    cin >> n >> m;
    vector<int> a(n);
    s = 0;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        s += a[i];
    }

    p[0] = a[0];
    for(int i = 1; i < n; i++) {
        p[i] = a[i] + p[i - 1];
    }

    for(int i = 0; i < m; i++) {
        long long l, r;
        cin >> l >> r;
        long long ans = cal(r) - cal(l - 1);
        printf("%lld\n", ans);
    }
}     

int main() {
    int t = 1;
    std :: cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
