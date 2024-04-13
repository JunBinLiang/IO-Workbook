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

const int N = 2e5 + 10, M = 1000;
const int INF = 1e9;
int a[N];
vector<int> g[N];
vector<int> di[M + 1];
int dp[N][M + 1];
int ans = 1;
int n, k;
void init() {
  for(int i = 1; i <= M; i++) {
    for(int j = i; j <= M; j += i) {
      di[j].push_back(i);
    }
  }
}

void dfs(int pa, int u) {
  for(int v : g[u]) {
    if(v == pa) continue; 
    dfs(u, v);
  }

  for(int d1 : di[a[u]]) {
    ll tot = 0;
    for(int v : g[u]) {
      if(v == pa) continue;
      tot += dp[v][d1];
    }

    dp[u][d1] = min((ll)(dp[u][d1]), tot);
    for(int d2 : di[d1]) {
      if(tot + 1 <= k && u == 1) ans = max(ans, d2);
      if(d1 * d2 <= M) {
        dp[u][d1 * d2] = min((ll)(dp[u][d1 * d2]), 1 + tot);
      }
    }
  }
}

void solve() {
  cin >> n >> k;
  
  for(int i = 0; i <= n; i++) g[i].clear();
  for(int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
  }

  for(int i = 0; i < n - 1; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    g[u].push_back(v);
    g[v].push_back(u);
  }

  for(int i = 0; i <= n; i++) {
    for(int j = 0; j <= M; j++) {
      dp[i][j] = INF;
    }
  }
  ans = 1;
  dfs(-1, 1);
  cout << ans * a[1] << endl;
}


int main(){
  int t = 1;
  init();
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
