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

/*void kill() {
  vector<int> a;
  for(int i = 0; i < 1000000; i++) a.push_back(i);
}*/

const long long INF = 10000000000000000ll;
void solve() {
  int n, K;
  cin >> n >> K;
  vector<int> a(n);
  for(int i = 0; i < n; i++) {
    cin >> a[i];
  }

  vector<vector<ll>> dp(n, vector<ll>(K + 1, INF));
  for(int i = 0; i < n; i++) {
    dp[i][0] = a[i];
    if(i) dp[i][0] += dp[i - 1][0];
    
    for(int k = 1; k <= K; k++) {
      long long mn = a[i];
      int op = 0;
      if(i > 0)
        dp[i][k] = min(dp[i][k], a[i] + dp[i - 1][k]);
      else dp[i][k] = a[i];
      for(int j = i - 1; j >= max(0, i - k); j--) {
        op++;
        mn = min(mn, a[j] + 0ll);
        ll v = mn * (op + 1);
        if(j) v += dp[j - 1][k - op];
        dp[i][k] = min(dp[i][k], v);
      }
    }
  }

  ll ans = INF;
  for(int i = 0; i <= K; i++) {
    ans = min(ans, dp[n - 1][i]);
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
