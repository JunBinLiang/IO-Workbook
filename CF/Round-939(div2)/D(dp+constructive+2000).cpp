#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <string.h>

using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define ve vector

vector<pair<int, int>> ops;
int a[20];

void dfs(int l, int r) {
  int sz = r - l  + 1;
  if(sz == 1) {
    ops.push_back({l, r});
    return;
  }
  for(int i = r - 1; i >= l; i--) {
    dfs(l, i);
    if(i != l)
        ops.push_back({l, i - 1});
  }
  ops.push_back({l, r});
}

void cal(int l, int r) {
  bool zero = false;
  for(int i = l; i <= r; i++) {
    if(a[i] == 0) zero = true;
  }
  if(!zero) {
    ops.push_back({l, r});
  } else {
    ops.push_back({l, r});
    ops.push_back({l, r});
  }
  dfs(l, r);
}

const int N = 20;
int dp[N][2];
pair<int, int> p[N][2];

void solve() {
  int n;
  cin >> n;
  for(int i = 1; i <= n; i++) {
    cin >> a[i];
  }

  memset(dp, 0, sizeof dp);

  for(int i = 1; i <= n; i++) {
    dp[i][0] = a[i];
    
    if(dp[i - 1][0] > dp[i - 1][1]) {
      dp[i][0] = a[i] + dp[i - 1][0];
      p[i][0] = {i - 1, 0};
    } else {
      dp[i][0] = a[i] + dp[i - 1][1];
      p[i][0] = {i - 1, 1};
    }
    
    for(int j = i; j >= 1; j--) {
      int sz = i - j + 1;
      int w = sz * sz;
      
      if(dp[j - 1][0] + w > dp[i][1]) {
        dp[i][1] = dp[j - 1][0] + w;
        p[i][1] = {j - 1, 0};
      }
      if(dp[j - 1][1] + w > dp[i][1]) {
        dp[i][1] = dp[j - 1][1] + w;
        p[i][1] = {j - 1, 1};
      }
    }
  }

  int i = -1, j = -1;
  if(dp[n][0] > dp[n][1]) {
    i = n;
    j = 0;
  } else {
    i = n;
    j = 1;
  }
  
  int ans = dp[i][j];
  while(i != 0) {
    pair<int, int>& pa = p[i][j];
    if(j != 0) {
      cal(pa.first + 1, i);
    }
    i = pa.first;
    j = pa.second;
  }
  
  cout << ans <<" " << ops.size() << endl;
  for(auto& pa : ops) {
    printf("%d %d\n", pa.first, pa.second);
  }
}

int main(){
  int t = 1;
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
