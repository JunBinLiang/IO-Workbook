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

//4:49 - 4:59
const int N = 60, M = 1e5 + 10;
ll dp[N][M];
pair<int, int> a[N];
void solve() {
  int n, x;
  cin >> n >> x;
  ll sumh = 0;
  for(int i = 1; i <= n; i++) {
    cin >> a[i].first >> a[i].second;
    sumh += a[i].second;
  }

  //dp[i][j]  maximum money remain of buying j items
  for(int i = 0; i <= n + 1; i++) {
    for(int j = 0; j <= sumh + 1; j++) {
      dp[i][j] = -1;
    }
  }

  dp[0][0] = 0;
  int tot = 0;  
  for(int i = 1; i <= n; i++) {
    int c = a[i].first, h = a[i].second;
    tot += h;
    for(int j = 0; j <= tot; j++) {
      dp[i][j] = dp[i - 1][j];
      if(j >= h && dp[i - 1][j - h] != -1 && dp[i - 1][j - h] >= c) {
        dp[i][j] = max(dp[i][j], dp[i - 1][j - h] - c);
      }
      if(dp[i][j] != -1) dp[i][j] += x;
    }
  }
  
  /*for(int i = 0; i <= n; i++) {
      for(int j = 0; j <= tot; j++) cout << dp[i][j] << " ";
      cout << endl;
  }*/

  int ans = 0;
  for(int h = 0; h <= tot; h++) {
    if(dp[n][h] != -1) ans = max(ans, h);
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
