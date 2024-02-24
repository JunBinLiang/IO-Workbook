#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string.h>

using namespace std;  
using ll = long long;

const int N = 1010;
int a[N][N], d[41][N][N];
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};
vector<pair<int, int>> g[41];
int n, m, k;

void bfs(int color) {
  vector<bool> vis(50);
  queue<pair<int, int>> q;
  for(int i = 0; i < g[color].size(); i++) {
    int r = g[color][i].first, c = g[color][i].second;
    d[color][r][c] = 0;
    q.push({r,  c});
    vis[color] = true;
  }
  

  while(q.size() > 0) {
    pair<int, int> p = q.front(); q.pop();
    int r = p.first, c = p.second;
    for(int i = 0; i < 4; i++) {
      int nr = r + dx[i], nc = c + dy[i];
      if(nr < 0 || nr >= n || nc < 0 || nc >= m || d[color][nr][nc] != -1) continue;
      d[color][nr][nc] = 1 + d[color][r][c];
      q.push({nr, nc});
    }

    if(!vis[a[r][c]]) {
      vis[a[r][c]] = true;
      for(int i = 0; i < g[a[r][c]].size(); i++) {
        int nr = g[a[r][c]][i].first, nc = g[a[r][c]][i].second;
        if(d[color][nr][nc] != -1) continue;
        d[color][nr][nc] = 1 + d[color][r][c];
        q.push({nr, nc});
      }
    }
  }
}

void solve() {
  scanf("%d%d%d", &n, &m, &k);
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      scanf("%d", &a[i][j]);
      g[a[i][j]].push_back({i, j});
    }
  }

  memset(d, -1, sizeof d);
  for(int i = 1; i <= k; i++) bfs(i);
  int q;
  scanf("%d", &q);
  while(q--) {
    int r1, c1, r2, c2;
    scanf("%d%d%d%d", &r1, &c1, &r2, &c2);
    int ans = abs(r1 - r2) + abs(c1 - c2);
    r1--; c1--; r2--; c2--;
    for(int i = 1; i <= k; i++) {
      ans = min(ans, 1 + d[i][r1][c1] + d[i][r2][c2]);
    }
    printf("%d\n", ans);
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

