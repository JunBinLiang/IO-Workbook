#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <set>
#include <string.h>

using namespace std;  
using ll = long long;


const int MOD = 1e9 + 7;
const int N = 250;
char mat[N][N];
int dp[251][2][2][(1 << 16) + 1];
int n, m;
int dfs(int pos, int cur, int cnt, int st) { 
  //[current position, current row has bit, not cover, state of vertical]
  if(pos == n * m) { //reach end
    return 1;
  }
  
  if(dp[pos][cur][cnt][st] != -1) return dp[pos][cur][cnt][st];
  
  int i = pos / m, j = pos % m;
  bool lastcol = (j == m - 1);
  int ans = 0;
  if(mat[i][j] == '.') {
    if(cur == 1) { //cover by the current row
      ans += dfs(pos + 1, lastcol ? 0 : cur, cnt, st | (1 << j)); //take
      ans %= MOD;
      ans += dfs(pos + 1, lastcol ? 0 : cur, cnt, st); //not take
      ans %= MOD;
    } else {
      //not take
      if((st & (1 << j)) > 0) {
        ans += dfs(pos + 1, lastcol ? 0 : cur, cnt, st); //not take
        ans %= MOD;
      } else {
        if(cnt + 1 <= 1) {
          ans += dfs(pos + 1, lastcol ? 0 : cur, cnt + 1, st); //not take
          ans %= MOD;
        }
      }
      //take
      ans += dfs(pos + 1, lastcol ? 0 : 1, cnt, st | (1 << j)); 
      ans %= MOD;
    }
  } else {
    ans += dfs(pos + 1, 0, cnt, (st & (1 << j)) > 0 ? st ^ (1 << j) : st);
    ans %= MOD;
  }
  return dp[pos][cur][cnt][st] = ans;
}

void solve() {
  cin >> n >> m;
  vector<string> a(n);
  for(int i = 0; i < n; i++) {
    cin >> a[i];
  }

  if(n < m) {
    for(int i = 0; i < n; i++) {
      for(int j = 0; j < m; j++) {
        mat[j][i] = a[i][j];
      }
    }
    swap(n, m);
  } else {
    for(int i = 0; i < n; i++) {
      for(int j = 0; j < m; j++) {
        mat[i][j] = a[i][j];
      }
    }
  }

  memset(dp, -1, sizeof dp);
  ll ans = dfs(0, 0, 0, 0);
  cout << ans << endl;
}


int main(){
  int t = 1;
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}

