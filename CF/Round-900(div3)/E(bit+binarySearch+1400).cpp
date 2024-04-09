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

const int N = 2e5 + 10;
int p[31][N];

void solve() {
  int n, m;
  scanf("%d", &n);

  for(int i = 0; i < 31; i++) p[i][0] = 0;

  for(int i = 1; i <= n; i++) {
    int x;
    scanf("%d", &x);
    for(int j = 0; j < 31; j++) {
      if(x & (1 << j)) p[j][i] = 1;
      else p[j][i] = 0;
    }
  }

  for(int i = 0; i < 31; i++) {
    for(int j = 2; j <= n; j++) p[i][j] += p[i][j - 1];
  }

  scanf("%d", &m);
  while(m--) {
    int l, k;
    scanf("%d%d", &l, &k);
    int L = l, R = n;
    int ans = -1;
    while(L <= R) {
      int mid = L + (R - L) / 2;
      int cnt = mid - l + 1;
      int s = 0;
      for(int i = 0; i < 31; i++) {
        if(p[i][mid] - p[i][l - 1] == cnt) s += (1 << i);
      }
      if(s >= k) ans = mid, L = mid + 1;
      else R = mid - 1;
    }
    printf("%d ", ans);
  }
  printf("\n");
}


int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
