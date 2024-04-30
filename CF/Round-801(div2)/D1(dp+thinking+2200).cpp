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

const int N = 2010;
vector<int> g[N];
int dp[N];
void dfs(int pa, int u) {
  int count = 0;
  for(int v : g[u]) {
    if(v == pa) continue;
    dfs(u, v);
    dp[u] += dp[v];
    if(dp[v] == 0) count++;
  }
  dp[u] += max(0, count - 1);
}

void solve() {
  int n;
  scanf("%d", &n);
  for(int i = 0; i <= n; i++) {
    g[i].clear();
    dp[i] = 0;
  }
  for(int i = 0; i < n - 1; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    g[u].push_back(v);
    g[v].push_back(u);
  }

  if(n == 1) {
    cout << 0 << endl;
    return;
  }

  int ans = n;
  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= n; j++) dp[j] = 0;
    dfs(-1, i);
    ans = min(ans, dp[i] + 1);
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

