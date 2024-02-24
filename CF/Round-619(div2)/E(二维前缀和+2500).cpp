#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string.h>

using namespace std;  
using ll = long long;
//R G Y B
const int N = 505;
char a[N][N];
int dp[4][N][N];
int s[251][N][N];
int n, m, q;

int query1(int i, int r1, int c1, int r2, int c2) {
  return dp[i][r2][c2] - dp[i][r2][c1 - 1] - dp[i][r1 - 1][c2] + dp[i][r1 - 1][c1 - 1];
}

int query2(int i, int r1, int c1, int r2, int c2) {
  return s[i][r2][c2] - s[i][r2][c1 - 1] - s[i][r1 - 1][c2] + s[i][r1 - 1][c1 - 1];
}

void solve() {
  scanf("%d%d%d", &n, &m, &q);
  for(int i = 1; i <= n; i++) {
    scanf("%s", a[i] + 1);
  }

  //memset(s, 0, sizeof s);
  //memset(dp, 0, sizeof dp);

  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= m; j++) {
      dp[0][i][j] = (a[i][j] == 'R') ? 1 : 0;
      dp[1][i][j] = (a[i][j] == 'G') ? 1 : 0;
      dp[2][i][j] = (a[i][j] == 'Y') ? 1 : 0;
      dp[3][i][j] = (a[i][j] == 'B') ? 1 : 0;
    }
  }

  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= m; j++) {
      for(int k = 0; k < 4; k++) {
        dp[k][i][j] += (dp[k][i - 1][j] + dp[k][i][j - 1] - dp[k][i - 1][j - 1]);
      }
    }
  }

  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= m; j++) {
      for(int k = 1; k <= 250; k++) {
        if(i + k * 2 - 1 > n || j + k * 2 - 1 > m) continue;
        int area = k * k;
        if(query1(0, i, j, i + k - 1, j + k - 1) == area && 
          query1(1, i, j + k, i + k - 1, j + 2 * k - 1) == area && 
          query1(2, i + k, j, i + 2 * k - 1, j + k - 1) == area && 
          query1(3, i + k, j + k, i + 2 * k - 1, j + 2 * k - 1) == area) {
            s[k][i][j] = 1;
        }
      }
    }
  }
  
  /*for(int k = 0; k < 4; k++) {
      for(int i = 1; i <= n; i++) {
          for(int j = 1; j <= m; j++) {
              cout << s[k][i][j] << " ";
          } cout << endl;
      }
      cout << endl;
  }*/

  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= m; j++) {
      for(int k = 1; k <= 250; k++) {
          s[k][i][j] += (s[k][i - 1][j] + s[k][i][j - 1] - s[k][i - 1][j - 1]);
      }
    }
  }



  while(q--) {
    int r1, c1, r2, c2;
    scanf("%d%d%d%d", &r1, &c1, &r2, &c2);
    int ans = 0;
    for(int k = 1; k <= 250; k++) {
      int mid = k;
      if(r1 + 2 * mid - 1 <= r2 && c1 + 2 * mid - 1 <= c2) {
        if(r1 <= r2 - 2 * mid + 1&& c1 <= c2 - 2 * mid + 1 && query2(mid, r1, c1, r2 - 2 * mid + 1, c2 - 2 * mid + 1) > 0) {
          ans = mid;
        }
      }
    }

    printf("%d\n", ans * ans * 4);
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

