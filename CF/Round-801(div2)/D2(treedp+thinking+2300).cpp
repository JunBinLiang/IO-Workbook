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

const int N = 2e5 + 10;
vector<int> g[N];
int dp[N], ans = -1;
int has[N];
void dfs(int pa, int u) {
  int count = 0;
  for(int v : g[u]) {
    if(v == pa) continue;
    dfs(u, v);
    dp[u] += dp[v];
    if(dp[v] == 0) count++;
  }
  dp[u] += max(0, count - 1);
  has[u] = count;
}

void dfs1(int pa, int u) {
  if(pa != -1) {
    int pav = dp[pa];
    int pac = has[pa];

    if(dp[u] == 0) {
      pac--;
    }

    pav -= dp[u];
    pav -= max(0, has[pa] - 1);
    pav += max(0, pac - 1);

    dp[u] += pav;
    dp[u] -= max(0, has[u] - 1);
    if(pav == 0) {
      has[u]++;
    }
    dp[u] += max(0, has[u] - 1);
    ans = min(ans, 1 + dp[u]);
  }

  for(int v : g[u]) {
    if(v == pa) continue;
    dfs1(u, v);
  }
} 

void solve() {
  int n;
  scanf("%d", &n);
  for(int i = 0; i <= n; i++) {
    g[i].clear();
    dp[i] = 0;
    has[i] = false;
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

  ans = n;
  dfs(-1, 1);
  ans = min(ans, dp[1] + 1);
  dfs1(-1, 1);
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

