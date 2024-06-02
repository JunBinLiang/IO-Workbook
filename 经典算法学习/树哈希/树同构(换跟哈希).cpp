//https://vjudge.net/problem/%E6%B4%9B%E8%B0%B7-P5043
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

const ull mask = std::chrono::steady_clock::now().time_since_epoch().count();
ull shift(ull x) {
  x ^= mask;
  x ^= x << 13;
  x ^= x >> 7;
  x ^= x << 17;
  x ^= mask;
  return x;
}

const int N = 100 + 10;
vector<int> g[N];
ull h[N];

unordered_map<int, int> f;
vector<ull> cur;

void getHash1(int pa, int u) {
  h[u] = 1;
  for (int v : g[u]) {
    if (v == pa) {
      continue;
    }
    getHash1(u, v);
    h[u] += shift(h[v]);
  }
}

void getHash2(int pa, int u) {
  if(u != 1) {
    ll oldh = h[pa];
    oldh -= shift(h[u]);
    h[u] += shift(oldh);
  }
  cur.push_back(h[u]);
  for(int v : g[u]) {
    if(v == pa) continue;
    getHash2(u, v);
  }
}


void solve() {
  int n;
  cin >> n;
  for(int i = 0; i < n; i++) {
    int m;
    cin >> m;
    for(int u = 1; u <= m; u++) {
      int v;
      cin >> v;
      if(v == 0) continue;
      g[u].push_back(v);
      g[v].push_back(u);
    }

    getHash1(-1, 1);
    cur.clear();
    getHash2(-1, 1);
        
    int ans = i + 1;
    for(ull v : cur) {
      if(f.find(v) == f.end()) {
        f[v] = i + 1;
      } else {
        ans = min(ans, f[v]);
      }
    }
    for(int j = 0; j <= m; j++) g[j].clear();
    printf("%d\n", ans);
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
