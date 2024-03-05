#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <set>
#include <string.h>

using namespace std;  
using ll = long long;
const int N = 1e5 + 10;
vector<int> g[N];
int d[N], f[N];
int e[N];
void dfs(int pa, int u, int h) {
  d[u] = h;
  f[u] = pa;
  for(int v : g[u]) {
    if(pa == v) continue;
    dfs(u, v, h + 1);
  } 
}

void solve() {
  int n, m;
  scanf("%d", &n);
  for(int i = 0; i <= n; i++) {
    g[i].clear();
    e[i] = 0;
  }
  map<pair<int, int>, int> mp;
  for(int i = 0; i < n - 1; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    if(u > v) swap(u, v);
    g[u].push_back(v);
    g[v].push_back(u);
    mp[{u, v}] = i;
  }
  
  dfs(-1, 1, 0);

  scanf("%d", &m);
  for(int i = 0; i < m; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    while(u != v) {
      if(d[u] < d[v]) {
        swap(u, v);
      }
      int a = u, b = f[u];
      if(a > b) swap(a, b);
      e[mp[{a, b}]] += (1 << i);
      u = f[u];
    }
  }
  
  int INF = 1e9;
  vector<bool> vis(1 << m);
  vector<int> dp(1 << m, INF);
  dp[0] = 0;
  for(int i = 0; i < n - 1; i++) {
      if(vis[e[i]] || e[i] == 0) continue;
      vis[e[i]] = true;
      for(int st = 0; st < (1 << m); st++) {
          dp[st | e[i]] = min(dp[st | e[i]], 1 + dp[st]);
      }
  }
  printf("%d\n", dp.back());
}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
