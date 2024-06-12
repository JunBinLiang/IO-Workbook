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
using ull = unsigned long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)

const int N = 2e5 + 10;
vector<int> g[N];
int dp[N][2];
int ans = 0;
void dfs1(int pa, int u) {
  if(pa != -1 && g[u].size() == 1) {
    dp[u][0] = 0; //not take
    dp[u][1] = 1; //take
    return;
  }

  dp[u][0] = 0;
  dp[u][1] = 1;
  for(int v : g[u]) {
    if(v == pa) continue;
    dfs1(u, v);
    dp[u][0] += max(dp[v][0], dp[v][1]);
    dp[u][1] += dp[v][0];
  }
}

void dfs2(int pa, int u) {
  if(pa != -1) {
    int t1 = dp[pa][0] - max(dp[u][0], dp[u][1]);
    int t2 = dp[pa][1] - dp[u][0];
    dp[u][0] += max(t1, t2);
    dp[u][1] += t1;
    int v = dp[u][0];
    if(g[u].size() == 1) v++; 
    ans = max(ans, v);
  }
  for(int v : g[u]) {
    if(v == pa) continue;
    dfs2(u, v);
  }
}

void solve() {
  int n;
  scanf("%d", &n);
  for(int i = 0; i <= n; i++) g[i].clear();
  for(int i = 0; i < n - 1; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    g[u].push_back(v);
    g[v].push_back(u);
  }

  dfs1(-1, 1);
  ans = dp[1][0];
  if(g[1].size() == 1) ans++;
  dfs2(-1, 1);
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
