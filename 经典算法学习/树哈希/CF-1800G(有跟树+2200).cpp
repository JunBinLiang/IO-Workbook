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

const int N = 2e5 + 10;
vector<int> g[N];
ull h[N];
bool dp[N];

void getHash(int pa, int u) {
  h[u] = 1;
  unordered_map<ull, int> f;
  for (int v : g[u]) {
    if (v == pa) {
      continue;
    }
    getHash(u, v);
    h[u] += shift(h[v]);
    if(f.find(h[v]) != f.end()) f.erase(h[v]);
    else f[h[v]] = v;
  }
  
  if(f.size() == 0) {
    dp[u] = true;
  } else if(f.size() == 1) {
    dp[u] = dp[(f.begin()) -> second];
  } else {
    dp[u] = false;
  }
  
}

void solve() {
  int n;
  cin >> n;
  for(int i = 0; i <= n; i++) {
    g[i].clear();
    dp[i] = false;
  }

  for(int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  getHash(-1, 1);
  if(dp[1]) cout << "YES" << endl;
  else cout << "NO" << endl;
  
}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
