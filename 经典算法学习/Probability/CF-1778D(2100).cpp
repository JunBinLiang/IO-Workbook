#include <bits/stdc++.h>
#pragma GCC optimize(3)
#define ll long long
#define pii pair<int, int>
#define pll pair<long long, long long>
#define F first
#define S second
#define endl '\n'
using namespace std;
const int inf = 0x3f3f3f3f;
const int mod = 998244353;


ll qmul(ll x, ll y){
    ll cur = x, ans = 1;
    while(y > 0){
        if(y & 1) ans = (ans * cur) % mod;
        cur = (cur * cur) % mod;
        y >>= 1;
    }
    return ans;
}


void solve(){
    int n; cin >> n;
    string a, b; cin >> a >> b;
    int cnt = 0;
    for(int i=0; i<n; i++) if(a[i] == b[i]) cnt++;

    ll f[n+1], g[n+1], dp[n+1];
    f[0] = g[0] = 1;
    for(int i=1; i<=n-1; i++){
        ll inv = (n - g[i-1] * i % mod) % mod;
        if(inv < 0) inv += mod;
        inv = qmul(inv, mod - 2);
        f[i] = (n + f[i-1] * i) % mod * inv % mod;
        g[i] = (n - i) * inv % mod;
    }

    dp[n] = 0;
    for(int i=n-1; i>=cnt; i--){
        dp[i] = f[i] + g[i] * dp[i+1];
        dp[i] %= mod;
    }

    cout << dp[cnt] << endl;

} 


int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    
    int t =1;
    cin >> t;
    while(t--)
    solve();
    return 0;
}
