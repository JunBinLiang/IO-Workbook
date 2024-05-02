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


bool good[20][20];
int bcount[1 << 17];
int dp[17][1 << 17];
int n;

void reset() {
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= (1 << n); j++) dp[i][j] = -1;
    }
    memset(good, false, sizeof good);
    
}

int dfs(int i, int st) {
  if(dp[i][st] != -1) return dp[i][st];
  int ans = bcount[st];
  for(int j = 0; j < n; j++) {
    if(st & (1 << j)) {
      if(good[i][j]) {
        ans = min(ans, dfs(j, st ^ (1 << j)));
      }
    }
  }
  return dp[i][st] = ans;
}

void solve() {
  cin >> n;
  vector<pair<string, string>> a(n);
  for(int i = 0; i < n; i++) {
    cin >> a[i].first >> a[i].second;
  }
  
  reset();

  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      if(a[i].first == a[j].first || a[i].second == a[j].second) {
        good[i][j] = true;
      }
    }
  }

  for(int st = 0; st < (1 << n); st++) {
    bcount[st] = 0;
    for(int i = 0; i < n; i++) {
      if(st & (1 << i)) bcount[st]++;
    }
  }

  int ans = n;
  for(int i = 0; i < n; i++) {
    int st = (1 << n) - 1;
    ans = min(ans, dfs(i, st ^ (1 << i)));
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
