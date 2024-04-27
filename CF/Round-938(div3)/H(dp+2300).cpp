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

const int N = 2510;
int f[N][15];

const int INF = 1e9;
int n, m, k;
int p[15], pdp[(1 << 14) + 2], cdp[(1 << 14) + 2];

char a[510][510];

void solve() {
  scanf("%d%d%d", &n, &m, &k);
  for(int i = 0; i < n; i++) {
    scanf("%s", a[i]);
  }

  p[0] = 1;
  for(int i = 1; i < 14; i++) {
    p[i] = p[i - 1] * 3;
  }

  for(int i = 0; i <= n * m; i++) {
    for(int j = 0; j < 14; j++) {
      f[i][j] = 0;
    }
  }

  for(int t = 0; t < k; t++) {
    int x, y, p;
    scanf("%d%d%d", &x, &y, &p);
    x--; y--;
    for(int i = 0; i < n; i++) {
      for(int j = 0; j < m; j++) {
        if(a[i][j] == '.') continue;
        for(int r = 1; r < 14; r++) {
          int d1 = abs(x - i);
          int d2 = abs(y - j);
          if(d1 * d1 + d2 * d2 <= r * r) {
            f[t][r] += p;
          }
        }
      }
    }
  }

  for(int i = 0; i <= (1 << 14); i++) {
    pdp[i] = -INF;
    cdp[i] = -INF;
  }
  pdp[0] = 0; 

  for(int i = 0; i < k; i++) {
    for(int st = 0; st < (1 << 14); st++) {
      cdp[st] = pdp[st];
      for(int j = 1; j < 14; j++) {
        if((st & (1 << j)) == 0) continue;
        int newst = st | (1 << j);
        int damage = f[i][j];
        cdp[st] = max(cdp[st], pdp[st ^ (1 << j)] + damage - p[j]);
      }
    }
    swap(pdp, cdp);
  }
  

  int res = -INF;
  for(int st = 0; st < (1 << 14); st++) {
    res = max(res, pdp[st]);
  }
  printf("%d\n", max(0, res));
}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
