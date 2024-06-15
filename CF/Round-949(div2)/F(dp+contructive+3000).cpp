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

const int N = 25000 + 10, M = 3800, INF = 1e9;
int a[N], dp[N][M], L[2][M], R[2][M];
vector<int> g[N];

void dfs(int u) {
  if(g[u].size() == 0) { //leaf
    for(int i = 1; i < M; i++) {
      if(i == a[u]) {
        dp[u][i] = INF;
      } else {
        dp[u][i] = 0;
      }
    }
    return;
  }

  if(g[u].size() == 1) {
    int c1 = g[u][0];
    dfs(c1);
    int ans = INF;
    for(int i = 1; i < M; i++) { //connect
      if(i == a[u]) {
        dp[u][i] = INF;
      } else {
        ans = min(ans, dp[c1][i] + i);
      }
    }
    for(int i = 1; i < M; i++) {
        if(i != a[u]) dp[u][i] = min(dp[c1][i], ans);
    }
    //cout << u << " " << ans << endl;
    if(u == 1) {
      printf("%d\n", ans);
    }
    return;
  } else if(g[u].size() == 2) {
    int c1 = g[u][0], c2 = g[u][1];
    dfs(c1); dfs(c2);
    int lmin = INF, rmin = INF;
    int merge = INF;
    for(int i = 1; i < M; i++) {
      if(i != a[u]) {
        lmin = min(lmin, dp[c1][i] + i);
        rmin = min(rmin, dp[c2][i] + i);
        merge = min(merge, dp[c1][i] + dp[c2][i] + i);
        /*if(u == 1 && i < 10) {
            cout << "gg " << i << " " << dp[c1][i] << " " << dp[c2][i] << endl;
            cout << lmin << " " << rmin << " " << merge << endl;
            cout << endl;
        }*/
      }
    }

    for(int i = 1; i < M; i++) {
      if(i != a[u]) {
       dp[u][i] = min(merge, min(dp[c1][i] + rmin, dp[c2][i] + lmin));
      } else {
        dp[u][i] = INF;  
      }
    }

    if(u == 1) {
      printf("%d\n", min(merge, lmin + rmin));
    }
  }
}

void solve() {
  int n;
  scanf("%d", &n);
  for(int i = 0; i <= n; i++) g[i].clear();
  for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
  for(int u = 2; u <= n; u++) {
    int p;
    scanf("%d", &p);
    g[p].push_back(u);
  }
  dfs(1);
} 

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
