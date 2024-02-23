#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string.h>

using namespace std;  

const int N = 2e5 + 10, M = 21;
const int INF = 1e9;
int cnt[M][N], dp[(1 << M) + 5], pdp[(1 << M) + 5];
int n, m;
void solve() {
  cin >> n >> m;
  vector<pair<int, int>> a(n);
  vector<int> b(m);
  for(int i = 0; i < n; i++) {
    cin >> a[i].first;
    a[i].second = i + 1;
  }

  for(int i = 0; i < m; i++) {
    cin >> b[i];
  }

  if(n < m) {
    cout << "NO" << endl;
    return;
  }

  sort(a.begin(), a.end());
  reverse(a.begin(), a.end());
  
  memset(cnt, -1, sizeof cnt);
  for(int i = 0; i < m; i++) {
    for(int r = 0, l = 0; r < n; r++) {
      while(l <= r && (a[r].first + 0ll) * (r - l + 1) >= b[i]) {
        cnt[i][l] = (r - l) + 1;
        l++;
      }
    }
  }

  memset(dp, -1, sizeof dp);
  for(int s = 1; s < (1 << m); s++) {
    for(int i = 0; i < m; i++) {
      if(s & (1 << i)) {
        int ps = s ^ (1 << i);
        if(ps == 0) {
          if(cnt[i][0] != -1) {
            dp[s] = cnt[i][0];
            pdp[s] = i;
          }
        } else {
          if(dp[ps] != -1 && cnt[i][dp[ps]] != -1) {
            if(dp[s] == -1 || (dp[s] > dp[ps] + cnt[i][dp[ps]])) {
              dp[s] = dp[ps] + cnt[i][dp[ps]];
              pdp[s] = i;
            }
          }
        }
      }
    }
  }

  int s = (1 << m) - 1;
  if(dp[s] == -1) {
    cout << "NO" << endl;
    return;
  }
  

  //output the answer
  printf("YES\n");
  vector<vector<int>> ans(m);
  while(s != 0) {
    int i = pdp[s];
    for(int j = dp[s] - 1; j >= max(dp[s ^ (1 << i)], 0); j--) {
      ans[i].push_back(a[j].second);
    }
    s = s ^ (1 << i);
  }

  for(int i = 0; i < ans.size(); i++) {
    printf("%d ", (int)(ans[i].size()));
    for(int x : ans[i]) printf("%d ", x);
    printf("\n");
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

