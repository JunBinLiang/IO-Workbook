#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <map>
#include <unordered_set>
#include <string.h>

using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define ve vector

int a[11][100000 + 10];
ll dp[100000 + 10][12];
int n, m, k;

ll dfs(int i, int count) {
    if(i > m) {
        return 0;
    }    
    if(dp[i][count] != -1) return dp[i][count];
    ll ans = 0;
    if(i + k - 1 <= m) {
        int curCount = 1 + count;
        for(int j = 1; j <= min(curCount, n); j++) {
            ans = max(ans, a[j][i] + dfs(i + 1, curCount - j));
        }
        ans = max(ans, dfs(i + 1, min(k - 1, curCount)));
    } else {
        int last = m - k + 1;
        int valid = min(count, last - (i - k + 1) + 1);
        //cout << i << " " << count << " " << valid << endl;
        for(int j = 1; j <= min(n, valid); j++) {
            ans = max(ans, a[j][i] + dfs(i + 1, valid - j));
        }
        ans = max(ans, dfs(i + 1, valid));
    }
    return dp[i][count] = ans;
}

void solve() {
  memset(a, 0, sizeof a);
  memset(dp, -1, sizeof dp);

  
  scanf("%d%d%d", &n, &m, &k);
  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= m; j++) {
      scanf("%d", &a[i][j]);
    }
  }

  for(int j = 1; j <= m; j++) {
    vector<int> b;
    for(int i = 1; i <= n; i++) b.push_back(a[i][j]);
    sort(b.begin(), b.end());
    reverse(b.begin(), b.end());
    for(int i = 1; i <= n; i++) {
      a[i][j] = b[i - 1];
      a[i][j] += a[i - 1][j];
    }
  }
  
  /*for(int i = 1; i <= n; i++) {
      for(int j = 1; j <= m; j++) cout << a[i][j] << " ";
      cout << endl;
  }
  cout << endl;*/


  cout << dfs(1, 0) << endl;
}


int main(){
  int t = 1;
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
