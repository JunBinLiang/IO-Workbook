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

int a[22][50010];
void solve() {
  int n, m;
  cin >> n >> m;
  for(int i = 1; i <= n; i++) {
    for(int j = 0; j < m; j++) {
      scanf("%d", &a[i][j]);
    }
  }

  fact[0] = 1;
  for(int i = 1; i < 21; i++) {
    fact[i] = fact[i - 1] * i;
    fact[i] %= MOD;
  }

  ll ans = 0;
  ll inv = modInverse(fact[n], MOD);
  for(int j = 0; j < m; j++) {
    vector<int> c(n + 1);
    for(int i = 1; i <= n; i++) {
      c[a[i][j] - 1]++;
    }

    ll w = fact[n];
    if(c[0] == 0) {
      int count = 0;
      ll p = 1;
      bool ok = true;
      for(int i = 1; i <= n; i++) {
        count++;
        if(c[i] > count) {
          ok = false;
          break;
        }
        p *= ((C(count, c[i]) * fact[c[i]]) % MOD);
        p %= MOD;
        count -= c[i];
      }
      if(ok) {
          w -= p;
          if(w < 0) w += MOD;
      }
    }
    
    ans += w;
    ans %= MOD;
  }

  cout << (ans * inv) % MOD << endl;
}

int main(){
  int t = 1;
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
