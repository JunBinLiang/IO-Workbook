#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <set>
#include <string.h>

using namespace std;  
using ll = long long;

const int MOD = 998244353;
const int N = 4e6 + 10;
ll fact[N];
ll fpow(ll x, int y){
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

void init() {
  fact[0] = 1;
  for(int i = 1; i < N; i++) {
    fact[i] = fact[i - 1] * i;
    fact[i] %= MOD;
  }
}

void solve() {
  vector<int> a(5);
  for(int i = 1; i <= 4; i++) {
    cin >> a[i];
  }

  //Good
  //1 -> 2 
  //1 -> 3
  //2 -> 1
  //2 -> 4
  //3 -> 2
  //3 -> 3
  //4 -> 1
  //4 -> 4
  if(a[1] + a[2] == 0) {
    if(a[3] == 0 || a[4] == 0) {
        cout << 1 << endl;
    } else {
        cout << 0 << endl;
    }
    return;
  }
  
  if(abs(a[1] - a[2]) > 1) {
    cout << 0 << endl;
    return;
  }

  ll ans = 0;
  if(a[1] == a[2]) {
    ll x = max(1ll, C(a[4] + a[2] + 1 - 1, a[4])) * max(1ll, C(a[3] + a[1] - 1, a[3]));
    x %= MOD;
    ll y = max(1ll, C(a[4] + a[2] - 1, a[4])) * max(1ll, C(a[3] + a[1] - 1 + 1, a[3]));
    y %= MOD;
    ans = (x + y) % MOD;
  } else {
    ans = max(1ll, C(max(a[1], a[2]) + a[3] - 1, a[3])) * max(1ll, C(max(a[1], a[2]) + a[4] - 1, a[4]));
    ans %= MOD;
  }

  cout << ans << endl;
  
}

int main(){
  int t = 1;
  init();
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}

