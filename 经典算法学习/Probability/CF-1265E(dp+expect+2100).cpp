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

const int MOD = 998244353;
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


//dp[i] : expect number to reach happy if start from position i
//dp[i] = p[i] * (1 + dp[i + 1]) + (1 - p[i]) * (1 + dp[1])
//dp[i] = 1 + p[i] * dp[i] + (1 - p[i]) * (dp[1])
//dp[n + 1] = 0

void solve() {
  int n;
  cin >> n;
  vector<ll> a(n);
  for(int i = 0; i < n; i++) {
    cin >> a[i];
    a[i] = a[i] * modInverse(100, MOD);
    a[i] %= MOD;
  }

  ll base = 1;
  ll ans = 0;
  ll cur = 1;
  for(int i = 0; i < n; i++) {
    base *= modInverse(a[i], MOD);
    base %= MOD;

    ans += cur;
    cur *= a[i];
    cur %= MOD;
    ans %= MOD;
  }
  cout << (ans * base) % MOD << endl;
}

int main(){
  int t = 1;
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
