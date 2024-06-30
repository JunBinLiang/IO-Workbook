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

ll inv(ll a, ll m) {
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
long long two;
long long count(long long n) {
  n %= MOD;
  if(n < 0) n += MOD;
  return (((((1 + n) % MOD) * n) % MOD) * two) % MOD;
}


map<pair<long long, int>, int> dp;
int dfs(long long n, int k) {
  if(n == 0 || k == 0) {
    return 0;
  }
  if(dp.find({n, k}) != dp.end()) {
    return dp[{n, k}];
  }
  
  if(n <= ((1ll << (k)))) {
    long long ans = 0;
    if(n == (1ll << (k))) {
      ans = count(n - 1);
    } else {
      ans = count(n);
    }
    return dp[{n, k}] = ans;
  }

  int ans = dfs(1ll << (k), k);
  for(int i = k + 1; i < 62; i++) {
    long long segment = (1ll << i);
    if(segment <= n) {
      ans += dfs(segment / 2, k - 1);
      ans %= MOD;
    } else {
      ans += dfs(n - segment / 2, k - 1);
      ans %= MOD;
      break;
    }
  }
  dp[{n, k}] = ans;
  //cout << n << " " << k << " " << ans << endl;
  return ans;
}

void solve() {
  long long n; int k;
  scanf("%lld%d", &n, &k);
  two = inv(2, MOD);
  int ans = dfs(n, k + 1); //use k + 1 to make more convinient
  printf("%d\n", ans);
}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}


