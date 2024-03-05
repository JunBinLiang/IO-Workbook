#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <unordered_set>
#include <string.h>

using namespace std;  
using ll = long long;

const int MOD = 998244353;
const int N = 5e5 + 10;
int a[N];
ll f[N];
vector<pair<int, int>> g;
vector<int> rk;

void init() {
  f[0] = 1;
  for(int i = 1; i < N; i++) {
    f[i] = f[i - 1] * i;
    f[i] %= MOD;
  }
}

ll fpow(ll x, int y){
	ll res = 1;
	while(y){
		if(y & 1) res = (res * x) % MOD;
		x = (x * x) % MOD;
		y >>= 1;
	}
	return res;
}  

ll C(int n, int m) {
  return f[n] * fpow(f[n - m], MOD - 2) % MOD * fpow (f[m], MOD - 2) % MOD;
}

void dfs(int u) {
  if(g[u].first != -1) {
    dfs(g[u].first);
  }
  rk.push_back(u);
  if(g[u].second != -1) {
    dfs(g[u].second);
  }
}

void solve() {
  int n, k;
  scanf("%d%d", &n, &k);

  g.clear();
  g.push_back({-1, -1});
  for(int i = 1; i <= n; i++) {
    int l, r, v;
    scanf("%d%d%d", &l, &r, &v);
    a[i] = v;
    g.push_back({l, r});
  }
  
  rk.clear();
  dfs(1);
  rk.push_back(0);
  a[0] = k;
  
  int p = -1;
  ll res = 1;
  for(int i = 0; i < rk.size(); i++) {
    int u = rk[i];
    if(a[u] == -1) {
    
    } else {
      int l = -1, r = -1, count = -1;
      if(p == -1) {
        l = 1; r = a[u]; count = i;
      } else {
        l = a[rk[p]]; r = a[u]; count = i - p - 1;
      }
      if(count > 0) {
        ll ways = 0;
        int options = r - l + 1;
        ll t = 1, mul = options;
        for(int j = 1; j <= count; j++) {
          if(options >= j) {
            t *= mul--;
            t %= MOD;
            ll x = ((t * fpow(f[j], MOD - 2)) % MOD) * C(count - 1, j - 1);
            x %= MOD;
            ways += x;
            ways %= MOD;
          }
        }
        res *= ways;
        res %= MOD;
      }
      p = i;
    }
  }
  printf("%lld\n", res);
}

int main(){
  init();
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
