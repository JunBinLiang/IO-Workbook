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
using ull = unsigned long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)


void solve() {
  int n, m;
  scanf("%d%d", &n, &m);
  vector<ll> a(n), b(m);
  for(int i = 0; i < n; i++) {
    scanf("%lld", &a[i]);
  }

  vector<vector<pair<ll, int>>> p(31);
  for(int i = 0; i < n; i++) {
    int best = 0;
    for(int j = 0; j <= 30; j++) {
      if((a[i] % (1ll << j)) == 0) {
        best = j;
      }
    }
    p[best].push_back({a[i], i});
  }

  for(int i = 0; i < m; i++) {
    int x;
    scanf("%d", &x);
    for(int j = x; j < p.size(); j++) {
      for(auto& pa : p[j]) {
        pa.first += (1ll << (x - 1));
        p[x - 1].push_back(pa);
      }
      
      p[j].clear();
    }
  }

  vector<ll> ans(n);
  for(int i = 0; i < p.size(); i++) {
    for(auto& pa : p[i]) {
      ans[pa.second] = pa.first;
    }
  }
  for(int i = 0; i < n; i++) {
    printf("%lld ", ans[i]);
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
