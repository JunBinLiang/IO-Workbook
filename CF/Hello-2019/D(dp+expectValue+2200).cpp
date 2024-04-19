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

const int N = 1e4 + 5;
ll dp[50][N];
ll inv[65];
ll n; int k;

ll dfs1(int x, int count, int op) {
  if(op == k) {
    if(count != x) return 0;
    return 1;
  }
  if(dp[count][op] != -1) {
    return dp[count][op];
  }
  ll ans = 0;
  for(int i = 0; i <= x; i++) {
    if(count + i > x) break;
    ans += (inv[i + count + 1] * dfs1(x, count + i, op + 1));
    ans %= MOD;
  }
  //cout << count << " " << op << " " << ans << endl;
  return dp[count][op] = ans;
}

ll ans = 0;
ll f[100][100];
void dfs2(vector<pair<ll, int>>& a, int i, ll p, ll v) {
  if(i >= a.size()) {
    ans += (v * p);
    ans %= MOD;
    return;
  }

  ll pro = 1;
  dfs2(a, i + 1, (f[i][0] * p) % MOD, v);
  for(int j = 1; j <= a[i].second; j++) {
    pro *= a[i].first;
    dfs2(a, i + 1, (f[i][j] * p) % MOD, (v * pro) % MOD);
  }
}

void solve() {
  cin >> n >> k;

  vector<pair<ll, int>> a;
  for(ll i = 2; i * i <= n; i++) {
    if(n % i == 0) {
      int count = 0;
      while(n % i == 0) {
        n /= i;
        count++;
      }
      a.push_back({i, count});
    }
  }
  if(n > 1) {
    a.push_back({n, 1});
  }

  for(int i = 1; i < 65; i++) {
    inv[i] = modInverse(i, MOD);
  }
  
  for(int i = 0; i < a.size(); i++) {
    auto& p = a[i];
    memset(dp, -1, sizeof dp);
    for(int j = 0; j <= p.second; j++) {
      f[i][j] = dfs1(p.second, j, 0);
    }    
  }
  
  dfs2(a, 0, 1, 1);
  cout << ans << endl;
}

int main(){
  int t = 1;
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
