#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <set>
#include <string.h>

using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define ve vector

const int N = 110;
int a[N][N];
int b[N][N], dp[N][N];
int n, m;
bool ok(int g) {
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      if(a[i][j] % g == 0) b[i][j] = 1;
      else b[i][j] = 0;
      dp[i][j] = 0;
    }
  }

  dp[0][0] = 1;
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      if(!b[i][j]) continue;
      if(i - 1 >= 0 && dp[i - 1][j]) dp[i][j] = 1;
      if(j - 1 >= 0 && dp[i][j - 1]) dp[i][j] = 1;
    }
  }

  return dp[n - 1][m - 1] == 1;
  
}

void solve() {
  scanf("%d%d", &n, &m);
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++){
      scanf("%d", &a[i][j]);
    }
  }

  int x = a[0][0];
  int ans = 1;
  for(int i = 1; i * i <= x; i++) {
    if(x % i == 0) {
      if(ok(i)) ans = max(ans, i);
      if(ok(x / i)) ans = max(ans, x / i);
    }
  }
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
