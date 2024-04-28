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

const int N = 1010;
char a[N][N];
void solve() {
  int n, m;
  scanf("%d%d", &n, &m);
  for(int i = 0; i < n; i++) {
    scanf("%s", a[i]);
  }

  int ans = 1e9;
  int r = -1, c = -1;
  vector<int> d1, d2;
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      if(a[i][j] == 'B') {
        //i + j
        //i - j
        d1.push_back(i + j);
        d2.push_back({i - j});
      }
    }
  }
  sort(d1.begin(), d1.end());
  sort(d2.begin(), d2.end());

  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      int c1 = i + j, c2 = i - j;
      int mx = 0;
      if(c1 >= d1[0]) mx = max(mx, c1 - d1[0]);
      if(c1 <= d1.back()) mx = max(mx, d1.back() - c1);
      if(c2 >= d2[0]) mx = max(mx, c2 - d2[0]);
      if(c2 <= d2.back()) mx = max(mx, d2.back() - c2);
      if(mx < ans) {
          ans = mx;
          r = i;
          c = j;
      }
    }
  }

  printf("%d %d\n", r + 1, c + 1);
}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}

