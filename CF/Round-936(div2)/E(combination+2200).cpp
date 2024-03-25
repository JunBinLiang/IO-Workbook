#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <map>
#include <set>
#include <string.h>

using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define ve vector


const int MOD = 1e9 + 7;
const int N = 2e5 + 10;
ll fact[N];
ll fpow(ll x, int y, ll MOD){
	ll res = 1;
	while(y){
		if(y & 1) res = (res * x) % MOD;
		x = (x * x) %MOD;
		y >>= 1;
	}
	return res;
}  

ll C(int n, int m) {
  return fact[n] * fpow(fact[n - m], MOD - 2, MOD) % MOD * fpow (fact[m], MOD - 2, MOD) % MOD;
}

void solve() {
  int n, m1, m2;
  scanf("%d%d%d", &n, &m1, &m2);
  vector<int> pref(m1), suf(m2);
  for(int i = 0; i < m1; i++) {
    scanf("%d", &pref[i]);
  }
  for(int i = 0; i < m2; i++) {
    scanf("%d", &suf[i]);
  }

  if(pref.back() != suf[0]) {
    cout << 0 << endl;
    return;
  }

  if(pref[0] != 1 || suf.back() != n) {
    cout << 0 << endl;
    return;
  }

  fact[0] = 1;
  for(int i = 1; i <= n; i++) {
    fact[i] = fact[i - 1] * i;
    fact[i] %= MOD;
  }

  ll w = C(n - 1, n - suf[0]);
  ll ans1 = 1, ans2 = 1;
  
  for(int i = pref.size() - 2; i >= 0; i--) {
    int d = pref[i + 1] - pref[i] - 1;
    ll ways = C((pref[i + 1] - 1) - 1, d) * fact[d];
    ways %= MOD;
    ans1 *= ways;
    ans1 %= MOD;
  }

  for(int i = 1; i < suf.size(); i++) {
    int d = suf[i] - suf[i - 1] - 1;
    ll ways = C((n - suf[i - 1] - 1), d) * fact[d];
    ways %= MOD;
    ans2 *= ways;
    ans2 %= MOD;
  }

  ll ans = (ans1 * ans2) % MOD;
  cout << (ans * w) % MOD << endl;
}


int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}

