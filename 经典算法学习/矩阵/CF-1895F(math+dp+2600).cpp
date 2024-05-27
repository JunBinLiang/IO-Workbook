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

using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define ve vector

const int MOD = 1e9 + 7;
const int N = 55;
ll a[N][N], f1[N];
int n, k, x;

void mul1() {
  ll temp[N];
  for(int i = 0; i <= x - 1; i++) temp[i] = f1[i];
  for(int c = 0; c <= x - 1; c++) {
    ll sum = 0;
    for(int r = 0; r <= x - 1; r++) {
      sum += (temp[r] * a[r][c]);
      sum %= MOD;
    }
    f1[c] = sum;
  }
}

void mul2() {
  ll temp[N][N];
  for(int i = 0; i <= x - 1; i++)
    for(int j = 0; j <= x - 1; j++)
      temp[i][j] = a[i][j];
            
  for(int i = 0; i <= x - 1; i++) {
    for(int j = 0; j <= x - 1; j++) {
      ll sum = 0;
      for(int k = 0; k <= x - 1; k++) {
        sum += temp[i][k] * temp[k][j];
        sum %= MOD;
      }
      a[i][j] = sum;
    }
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

void solve() {
  cin >> n >> x >> k;
  //f(0, M) - f(0, x - 1) - f(x + k, M)
  //f(0, x - 1) can solve with dp

  //f(0, M) - f(x + k, M)
  // For a given difference array, if we start a[0] as 0, min is the minimum prefix change and max is the maximum prefix change
  // Let x are the possible start number that is valid for the given difference array
  // L <= x + min, x + max <= R   
  // How many possible x for given (L, R)

  // L <= x + min <= R
  // L <= x + max <= R
  // L - min <= x <= R - min
  // L - max <= x <= R - max
  
  // L - min <= x <= R - max
  // x = max(0, (R - L) - max + min)    

  //f(0, M) - f(x + k, M), for each given difference array:
  // max(0, (M - 0) - max + min)  - max(0, (M - (x + k)) - max + min)    

  //-max + min is constant
  //max(0, M - c) - max(0, M - (x + k) - c)

  //M is very big
  // (M - c) - M + (x + k) + c
  // (x + k)

  ll ans = (x + k) * fpow(2 * k + 1, n - 1);
  ans %= MOD;
  
  //calculate f(0, x - 1)

  if(x == 0) {
    cout << ans << endl;
    return;
  }

  //construct matrix
  memset(a, 0, sizeof a);
  memset(f1, 0, sizeof f1);
  for(int i = 0; i <= x - 1; i++) {
    f1[i] = 1;
  }
  for(int c = 0; c <= x - 1; c++) {
    for(int r = 0; r <= x - 1; r++) {
      if(abs(c - r) <= k) {
        a[r][c] = 1;
      }
    }
  }

  n--;
  while(n) {
    if (n & 1) mul1();  // res = res * a
    mul2();  // a = a * a
    n >>= 1;
  }

  for(int i = 0; i <= x - 1; i++) {
    ans -= f1[i];
    if(ans < 0) ans += MOD;
  }

  cout << ans << endl;
}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
