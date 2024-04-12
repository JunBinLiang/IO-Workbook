#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <string.h>

using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define ve vector

const int N = 2e5 + 10;
char s[N];
pair<int, int> lp[N], rp[N];
map<pair<int, int>, vector<int>> leftv, rightv;

bool search(vector<int>& a, int L, int R) {
  int l = 0, r = a.size() - 1;
  int p = -1;
  while(l <= r) {
    int mid = l + (r - l) / 2;
    if(a[mid] >= L) {
      p = a[mid];
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }
  return p != -1 && p >= L && p <= R;
}

void solve() {
  int n, m;
  scanf("%d%d", &n, &m);
  scanf("%s", s + 1);
  int x = 0, y = 0;
  for(int i = 1; i <= n; i++) {
    if(s[i] == 'U') {
      y++;
    } else if(s[i] == 'D') {
      y--;
    } else if(s[i] == 'L') {
      x--;
    } else {
      x++;
    }
    lp[i] = {x, y};
    leftv[{x, y}].push_back(i);
  }

  x = 0; y = 0;
  for(int i = n; i >= 1; i--) {
    if(s[i] == 'U') {
      y++;
    } else if(s[i] == 'D') {
      y--;
    } else if(s[i] == 'L') {
      x--;
    } else {
      x++;
    }
    rp[i] = {x, y};
    rightv[{x, y}].push_back(i);
  }
  for(auto it = rightv.begin(); it != rightv.end(); it++) {
    vector<int>& p = it -> second;
    reverse(p.begin(), p.end());
  }
  lp[0] = {0, 0};
  rp[n + 1] = {0, 0};
  

  for(int i = 0; i < m; i++) {
    int x, y, l, r;
    scanf("%d%d%d%d", &x, &y, &l, &r);
    
    if(x == 0 && y == 0) {
      printf("YES\n");
      continue;
    }
 
    if(leftv.find({x, y}) != leftv.end() && leftv[{x, y}][0] < l) {
      printf("YES\n");
      continue;
    }

    int xshift = -lp[l - 1].first, yshift = -lp[l - 1].second;
    xshift += rp[r + 1].first, yshift += rp[r + 1].second;
    if(rightv.find({x + xshift, y + yshift}) != rightv.end()) {
      if(search(rightv[{x + xshift, y + yshift}], l, r)) {
        printf("YES\n");
        continue;
      }
    }

    if(leftv.find({x, y}) != leftv.end()) {
      if(r + 1 <= n && search(leftv[{x, y}], r + 1, n)) {
        printf("YES\n");
        continue;
      }
    }
  
    printf("NO\n");
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
