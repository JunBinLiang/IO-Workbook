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

const int N = 1e6 + 10;
int vis[N], row[N], col[N];
int rdp[N], cdp[N];
int l, r, u, d, sz;

int n, m;

int id(int i, int j) {
    return i * m + j;
}

bool in(int i, int j) {
  return i >= 0 && i < n && j >= 0 && j < m;
}


void dfs(vector<string>& mat, int i, int j) {
  if(!in(i, j)) return;
  if(mat[i][j] == '.' || vis[id(i, j)]) return;
  l = min(l, j);
  r = max(r, j);
  u = min(u, i);
  d = max(i, d);
  vis[id(i, j)] = true;
  sz++;
  dfs(mat, i + 1, j);
  dfs(mat, i - 1, j);
  dfs(mat, i, j + 1);
  dfs(mat, i, j - 1);
}

void solve() {
  cin >> n >> m;
  vector<string> mat(n);
  for(int i = 0; i <= n * m; i++) vis[i] = false;
  for(int i = 0; i < n; i++) {
    cin >> mat[i];
  }
  
  for(int i = 0; i < n; i++) {
    row[i] = 0;
    rdp[i] = 0;
    for(int j = 0; j < m; j++) {
      if(mat[i][j] == '#') row[i]++;
    }
  }
  
  for(int j = 0; j < m; j++) {
    col[j] = 0;
    cdp[j] = 0;
    for(int i = 0; i < n; i++) {
      if(mat[i][j] == '#') col[j]++;
    }
  }
  
  vector<vector<int>> dp(n, vector<int>(m, 0));
  
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      if(mat[i][j] == '#' && !vis[id(i, j)]) {
        l = m + 1; r = -1;
        u = n + 1; d = -1;
        sz = 0;
        dfs(mat, i, j);
        l = max(l - 1, 0); 
        r = min(r + 1, m - 1);
        u = max(u - 1, 0);
        d = min(d + 1, n - 1);
        //cout << u << " " << d << " " << l << " " << r << " " << sz << endl;

        for(int row = u; row <= d; row++) {
          for(int col = l; col <= r; col++) {
            dp[row][col] += sz;
          }
        }
        
        for(int row = u; row <= d; row++) rdp[row] += sz;
        for(int col = l; col <= r; col++) cdp[col] += sz;
        
      }
    }
  }
  
  
  /*for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      cout << dp[i][j] << " "; 
    } cout << endl;
  }*/
  
  int ans = 0;
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      int cnt = rdp[i] + cdp[j] - dp[i][j];
      cnt -= row[i];
      cnt -= col[j];
      if(mat[i][j] == '#') cnt++;
      cnt += (n + m - 1);
      ans = max(ans, cnt);
    }
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
