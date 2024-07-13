#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include <string.h>

using namespace std;

const int MOD = 1e9 + 7;
const int N = 1e6 + 10;
using ll = long long;
ll f[N];

ll fpow(ll x, int y){
	ll res = 1;
	while(y){
		if(y & 1) res = (res * x) % MOD;
		x = (x * x) % MOD;
		y >>= 1;
	}
	return res;
} 
  
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

long long mul(long long x, long long y) {
    return (x * y) % MOD;
}

ll C(int n,int m) {
  return f[n] * fpow(f[n - m], MOD - 2) % MOD * fpow(f[m], MOD - 2) % MOD;
}


void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    int sp = k, nsp = n - k;
    long long s1 = 0, s2 = 0;
    
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        if(i < k) s1 += a[i];
        else s2 += a[i];
    }
    s1 %= MOD;
    s2 %= MOD;

    f[0] = 1;
    for(int i = 1; i <= n * 2; i++) {
        f[i] = (f[i - 1] * i) % MOD;
    }
    
    long long ways = C(sp + (nsp + 1) - 1, sp);
    long long base = (modInverse(f[nsp], MOD) * modInverse(f[sp], MOD)) % MOD;
    base = mul(base, modInverse(ways, MOD));

    long long non1 = mul((nsp + 1) / 2, f[nsp - 1]);
    non1 = mul(non1, f[sp]);
    non1 = mul(non1, s2);
    non1 = mul(non1, ways);
   
    long long spe1 = mul((nsp + 2) / 2, f[nsp]);
    spe1 = mul(spe1, f[sp - 1]);
    spe1 = mul(spe1, s1);
    spe1 = mul(spe1, C(sp - 1 + (nsp + 2) - 1, sp - 1));
    
    long long ans1 = (non1 + spe1) % MOD;
    ans1 *= base; ans1 %= MOD;


    long long non2 = mul((nsp) / 2, f[nsp - 1]);
    non2 = mul(non2, f[sp]);
    non2 = mul(non2, s2);
    non2 = mul(non2, ways);
   
    long long spe2 = mul((nsp + 1) / 2, f[nsp]);
    spe2 = mul(spe2, f[sp - 1]);
    spe2 = mul(spe2, s1);
    spe2 = mul(spe2, C(sp - 1 + (nsp + 2) - 1, sp - 1));
    
    long long ans2 = (non2 + spe2) % MOD;
    ans2 *= base; ans2 %= MOD;

    printf("%lld %lld\n", ans1, ans2);
}   

int main() {
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
