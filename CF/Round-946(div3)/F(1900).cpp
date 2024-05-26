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

using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define ve vector

void solve() {
  int a, b, n, m;
  cin >> a >> b >> n >> m;

  map<int, vector<int>> rows, cols;
  for(int i = 0; i < n; i++) {
    int x, y;
    cin >> x >> y;
    rows[x].push_back(y);
    cols[y].push_back(x);
  }

  int ans1 = 0, ans2 = 0;
  int U = 1, D = a; //[U : D]
  int L = 1, R = b; //[L : R]
  for(int i = 0; i < m; i++) {
    char c; int k;
    cin >> c >> k;
    int s = 0;
    if(c == 'U') {
      U += k;
      while(true) {
        auto it = rows.begin();
        if(it == rows.end() || it -> first >= U) break;
        int r = it -> first;
        auto v = it -> second;
        for(int c : v) {
          if(c >= L && c <= R) s++;
        }
        rows.erase(r);
      }
    } else if(c == 'D') {
      D -= k;
      while(rows.size() > 0) {
        auto it = rows.end();
        it--;
        if(it -> first <= D) break;
        int r = it -> first;
        auto v = it -> second;
        for(int c : v) {
          if(c >= L && c <= R) s++;
        }
        rows.erase(r);
      }
    } else if(c == 'L') {
      L += k;
      while(true) {
        auto it = cols.begin();
        if(it == cols.end() || it -> first >= L) break;
        int c = it -> first;
        auto v = it -> second;
        for(int r : v) {
          if(r >= U && r <= D) s++;
        }
        cols.erase(c);
      }
    } else {
      R -= k;
      while(cols.size() > 0) {
        auto it = cols.end();
        it--;
        if(it -> first <= R) break;
        int c = it -> first;
        auto v = it -> second;
        for(int r : v) {
          if(r >= U && r <= D) s++;
        }
        cols.erase(c);
      }
    }
    if(i % 2 == 0) ans1 += s;
    else ans2 += s;
  }
  cout << ans1 << " " << ans2 << endl;
}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
