#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <unordered_set>
#include <string.h>

using namespace std;  
using ll = long long;
void solve() {
  int n, x, y, s;
  cin >> n >> x >> y >> s;

  int m = x % y, c1 = x / y;
  if((n + 0ll) * m > s || (s - n * m) % y != 0) {
    printf("NO\n");
    return;
  }

  int tot = (s - n * m) / y;
  if(tot < c1) {
    printf("NO\n");
    return;
  }

  int INF = 1e9;
  vector<int> dp(s + 1, INF), p(s + 1);
  dp[0] = 0;
  
  for(int i = 1; i < dp.size(); i++) {
    for(int j = 1; (1 + j) * j / 2 <= i; j++) {
      if(dp[i - ((1 + j) * j / 2)] + 1 + j < dp[i]) {
        dp[i] = dp[i - ((1 + j) * j / 2)] + 1 + j;
        p[i] = j;
      }
    }
  }

  for(int i = c1; (c1 + i) * (i - c1 + 1) / 2 <= s; i++) {
    int sum = (c1 + i) * (i - c1 + 1) / 2;
    if(sum > tot) break;
    if(dp[tot - sum] + (i - c1 + 1) <= n) {
      printf("YES\n");
      vector<int> ans(n, m);
      int index = 0;
      for(int j = 0; j <= i - c1; j++) {
        ans[index++] += (c1 + j) * y;
      }
      int v = tot - sum;
      while(v != 0) {
        int step = p[v];
        v -= ((1 + step) * step / 2);
        for(int j = 0; j <= step; j++) {
          ans[index++] += j * y;
        }
      }
      for(int x : ans) printf("%d ", x);
      printf("\n");
      return;
    }
  }


  printf("NO\n");
}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
