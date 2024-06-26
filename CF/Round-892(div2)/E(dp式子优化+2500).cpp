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

const int N = 3010;
const long long INF = 100000000000000ll;
long long dp[N][N];
void solve() {
  int n, k;
  scanf("%d%d", &n, &k);
  vector<int> a(n + 1), b(n + 1);
  for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
  for(int i = 1; i <= n; i++) scanf("%d", &b[i]);

  //init dp
  for(int i = 0; i <= n + 1; i++) {
    for(int j = 0; j <= k + 1; j++) {
      dp[i][j] = 0;
    }
  }

  /*
  (b[l] - a[r]) + (b[r] - a[l]) => (b[l] -a[l]) + (b[r] - a[r])
  (-b[l] + a[r]) + (b[r] - a[l]) => (-b[l] - a[l]) + (b[r] + a[r])
  (b[l] - a[r]) + (-b[r] + a[l]) => (b[l] + a[l]) + (-b[r] - a[r])
  (-b[l] + a[r]) + (-b[r] + a[l]) => (-b[l] + a[l]) + (-b[r] + a[r])
  */

  /*
  dp[i][j] = f(i - len + 1, i) + dp[i - len][j - len]  
  prefix on dp[i - 1][j - 1] + f(i - 1 + 1, i)
            dp[i - 2][j - 2] + f(i - 2 + 1, i) ...
            ...
            dp[i - k][j - k]
  */
  vector<long long> t1(n + 1, -INF), t2(n + 1, -INF), t3(n + 1, -INF), t4(n + 1, -INF);
  t1[0] = b[1] - a[1];
  t2[0] = -b[1] - a[1];
  t3[0] = b[1] + a[1];
  t4[0] = -b[1] + a[1];

  for(int i = 1; i <= n; i++) {
    for(int j = 0; j <= min(i, k); j++) {
      //this is ok because j is alwyas less than i
      int slope = i - j;
      dp[i][j] = dp[i - 1][j];
      if(j != 0) {
        dp[i][j] = max(dp[i][j], b[i] - a[i] + t1[slope]);
        dp[i][j] = max(dp[i][j], b[i] + a[i] + t2[slope]);
        dp[i][j] = max(dp[i][j], -b[i] - a[i] + t3[slope]);
        dp[i][j] = max(dp[i][j], -b[i] + a[i] + t4[slope]);
      }
      
      if(i + 1 <= n) {
        t1[slope] = max(t1[slope], dp[i][j] + b[i + 1] - a[i + 1]); //0
        t2[slope] = max(t2[slope], dp[i][j] - b[i + 1] - a[i + 1]); //-2n
        t3[slope] = max(t3[slope], dp[i][j] + b[i + 1] + a[i + 1]); //2n
        t4[slope] = max(t4[slope], dp[i][j] - b[i + 1] + a[i + 1]); //0
      }
    }
  }
  printf("%lld\n", dp[n][k]);
}

/*
|7 - 5 | = 7 - 5
|5 - 7| = -5 + 7 
|a - b| + |c - d|
(b[l] - a[r]) + (b[r] - a[l])
(-b[l] + a[r]) + (b[r] - a[l])
(b[l] - a[r]) + (-b[r] + a[l])
(-b[l] + a[r]) + (-b[r] + a[l])
 */

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
