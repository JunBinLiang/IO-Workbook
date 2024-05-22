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

const int MOD = 998244353;
const int N = 1e6 + 10;
ll f[N];

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

ll divide(ll x, ll y) {
  return (x * modInverse(y, MOD)) % MOD;
}

void solve() {
  int n, k;
  scanf("%d%d", &n, &k);
  vector<int> a(n);
  for(int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }

  f[0] = 1;
  for(int i = 1; i <= n; i++) {
    f[i] = f[i - 1] * i;
    f[i] %= MOD;
  }

  sort(a.begin(), a.end());
  reverse(a.begin(), a.end());

  vector<int> first(n, n);
  for(int i = 0, j = 0; i < n; i++) {
    while(j < n && a[i] - a[j] <= k) j++;
    if(j < n && a[i] - a[j] > k) {
      first[i] = j;
    }
  }
  
  vector<ll> dp(n + 1, 0);
  if(a[0] - a[1] > k) {
    dp[1] = 1;
  }

  for(int i = 1; i < n; i++) {
    int conflict = first[i] - i - 1;
    dp[i + 1 + conflict] = dp[i + 1 + conflict] + (dp[i] * divide(f[i + conflict - 1], f[i - 1])) % MOD;
    dp[i + 1 + conflict] %= MOD;
    dp[i + 1] += (dp[i] * i);
    dp[i + 1] %= MOD;
  }

  cout << dp[n] << endl;

}
  

int main(){
  int t = 1;
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
