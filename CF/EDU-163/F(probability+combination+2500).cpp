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
const int N = 3e5 + 10, M = 1e6 + 10;
int a[N], b[N];
ll fact[M];

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
    return fact[n] * fpow(fact[n - m], MOD - 2) % MOD * fpow (fact[m], MOD - 2) % MOD;
}

int get(vector<int>& p, int l, int r) {
  return p[r] - p[l - 1];
}

void solve() {
  int n, m;
  scanf("%d%d", &n, &m);
  FOR(i, 1, n + 1) scanf("%d", &a[i]);
  FOR(i, 1, n + 1) scanf("%d", &b[i]);

  vector<int> p1(n + 1), p2(n + 1);
  for(int i = 1; i <= n; i++) p1[i] = a[i], p1[i] += p1[i - 1];
  for(int i = 1; i <= n; i++) p2[i] = b[i], p2[i] += p2[i - 1];

  fact[0] = 1;
  for(int i = 1; i < M; i++) fact[i] = (fact[i - 1] * i) % MOD;

  ll base = modInverse(fpow(2, p2.back()), MOD);
  vector<ll> fp(p2.back() + 1); //factorial prefixsum
  for(int i = 0; i < fp.size(); i++) {
    fp[i] = C(p2.back(), i);
    if(i > 0) {
        fp[i] += fp[i - 1];
        fp[i] %= MOD;
    }
  }

  while(m--) {
    int l, r;
    scanf("%d%d", &l, &r);
    int s1 = get(p1, l, r), other1 = p1.back() - s1;
    int s2 = get(p2, l, r), other2 = p2.back() - s2;
    
    int cur = s1, other = other1 + other2;
    int need = max(0, other - cur + 1); //at least 
    //cout << need <<" " << p2.back() << endl;
    if(need <= p2.back()) {
      ll prob = (fp.back() - (need > 0 ? fp[need - 1] : 0)) % MOD;
      if(prob < 0) prob += MOD;
      ll ans = (prob * base) % MOD;
      printf("%lld ", ans);
    } else {
      printf("0 ");
    }
  }
}

int main(){
  int t = 1;
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
