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
#include <random>
#include <chrono>

using namespace std;
using ll = long long;

const int N = 5e5 + 10;
vector<int> p[N], h[N];
int cnt[N];
void init() {
  memset(cnt, 0, sizeof cnt);
  for(int i = 1; i < N; i++) {
    for(int j = i; j < N; j += i) {
      p[j].push_back(i);
    }
  }
}


void solve() {
  int n;
  scanf("%d", &n);
  vector<int> a(n + 1);
  for(int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
  }

  /*long long ans = 0;
  for(int i = 1; i <= n; i++) {
    int g = __gcd(a[i], i);
    int x2 = a[i] / g, y2 = i / g;
    for(int y1 : p[x2]) {
      if(f[y1].find(y2) != f[y1].end()) {
        ans += f[y1][y2];
      }
    }
    for(int y1 : p[x2]) {
      f[y2][y1]++;
    }
  }*/

  long long ans = 0;
  vector<pair<int, int>> b;
  for(int i = 1; i <= n; i++) {
    int g = __gcd(a[i], i);
    int x2 = a[i] / g, y2 = i / g;
    b.push_back({y2, x2});
    h[x2].push_back(y2);
  }
  
  sort(b.begin(), b.end());
  for(int i = 0; i < b.size(); i++) {
    int j = i;
    while(j < b.size() && b[j].first == b[i].first) {
      int x1 = b[j].second, y1 = b[j].first;
      for(int d : p[x1]) {
        cnt[d]++;
      }
      j++;
    }

    bool skip = false;
    int x1 = b[i].second, y1 = b[i].first;
    for(int x2 = y1; x2 <= n; x2 += y1) {
      for(int y2: h[x2]) {
        if(y2 == y1 && x2 == x1 && !skip) { //skip match with itself
            skip = true;
            continue;
        }
        
        ans += cnt[y2];
      }
    }

    for(int k = i; k < j; k++) {
      for(int d : p[b[k].second]) {
        cnt[d] = 0;
      }
    }
    i = j - 1;
  }
  
  for(int i = 1; i <= n; i++) {
    int g = __gcd(a[i], i);
    int x1 = a[i] / g;
    h[x1].clear();
  }

  printf("%lld\n", ans / 2);
}

int main(){
  init();
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}


