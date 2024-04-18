#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <string.h>

using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define ve vector

const int MOD = 1e9 + 7;
const int N = 2e5 + 10;
ll fact[N];

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

ll fpow(ll x, int y) {
	ll res = 1;
	while(y){
		if(y & 1) res = (res * x) % MOD;
		x = (x * x) % MOD;
		y >>= 1;
	}
	return res;
} 

ll C(int n,int m) {
  return fact[n] * fpow(fact[n - m], MOD - 2) % MOD * fpow(fact[m], MOD - 2) % MOD;
}

void solve() {
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);
  ll s = 0;
  for(int i = 0; i < m; i++) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    s += w;
    s %= MOD;
  }

  if(m == 0) {
    cout << 0 << endl;
    return;
  }

  fact[0] = 1;
  for(int i = 1; i <= k; i++) {
    fact[i] = fact[i - 1] * i;
    fact[i] %= MOD;
  }

  ll tot = (n - 1ll) * n / 2;
  ll inv = modInverse(tot % MOD, MOD);
  ll p1 = (inv * 1) % MOD, p2 = ((tot - 1) * inv) % MOD;
  ll two = modInverse(2, MOD);

  //is select i times
  ll ans = 0;
  for(int i = 1; i <= k; i++) {
    ll ways = C(k, i);
    ll p = (fpow(p1, i) * fpow(p2, k - i)) % MOD;
    p *= ways;
    p %= MOD;
    ll v = (s + s + (i - 1ll) * m);
    v %= MOD;
    v *= i;
    v %= MOD;
    v *= two;
    v %= MOD;
    p *= v;
    p %= MOD;
    ans += p;
    ans %= MOD;
  }

  printf("%lld\n", ans);
}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
