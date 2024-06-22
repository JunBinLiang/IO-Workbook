#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <string.h>
#include <random>
#include <chrono>

using namespace std;
using ll = long long;
const int MOD = 1e9 + 7;
ll fpow(ll x, int y){
	ll res = 1;
	while(y){
		if(y & 1) res = (res * x) % MOD;
		x = (x * x) % MOD;
		y >>= 1;
	}
	return res;
} 

void solve() {
  long long l, r, k;
  cin >> l >> r >> k;

  //k * D(n) == D(k * n)
  //no carray over

  cout << (fpow(9/ k + 1, r) - fpow(9 / k + 1, l) + MOD) % MOD << endl;
}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
