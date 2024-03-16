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

//3:05 - 3:57
const int N = 2e5 + 10;
int p1[N][31], p2[N][31];

int bit(int n) {
  for(int i = 30; i >= 0; i--) {
    if(n & (1 << i)) return i;
  }
  return -1;
}

void solve() {
  int n, m;
  scanf("%d", &n);
  vector<pair<int, int>> a(n + 1);
  for(int i = 1; i <= n; i++) {
    scanf("%d%d", &a[i].first, &a[i].second);
  }

  for(int i = 0; i <= n; i++) {
    for(int j = 0; j < 31; j++) {
      p1[i][j] = 0;
      p2[i][j] = 0;
    }
  }

  for(int i = 1; i <= n; i++) {
    int x = a[i].first, y = a[i].second;
    for(int j = 30; j >= 0; j--) {
      int b1 = 0, b2 = 0;
      if(x & (1 << j)) b1 = 1;
      if(y & (1 << j)) b2 = 1;
      if(b1 == b2) {
        if(b1 == 1) {
          p1[i][j] = 1;
          x -= (1 << j);
          y -= (1 << j);
        }
      } else {
        if(x < y) swap(x, y);
        break;
      }
    }

    for(int j = 0; j < 30; j++) {
      if(x & (1 << j)) {
        p2[i][j] = 1;
      }
    }
  }

  //  1001010
  //  1111111
  // 10100000

  for(int i = 1; i <= n; i++) {
    for(int j = 0; j < 31; j++) {
      p1[i][j] += p1[i - 1][j];
      p2[i][j] += p2[i - 1][j];
    }
  }



  scanf("%d", &m);
  while(m--) {
    int l, r;
    scanf("%d%d", &l, &r);
    int ans = 0;
    for(int j = 30; j >= 0; j--) {
      int s1 = p1[r][j] - p1[l - 1][j];
      int s2 = p2[r][j] - p2[l - 1][j];
      if(s1 > 0) {
        ans |= (1 << j);
        if(s2 > 0) ans |= ((1 << j) - 1);
      } else {
        if(s2 > 0) ans |= (1 << j);
        if(s2 > 1) ans |= ((1 << j) - 1);
      }
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

//1010
//0011

