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

const int N = 3e5 + 10;
vector<int> g[N];
int h[N];
void dfs(int pa, int u) {
  h[u] = 1;
  for(int v : g[u]) {
    if(v == pa) continue;
    dfs(u, v);
    h[u] = max(h[u], 1 + h[v]);
  }
}

void solve() {
  int n;
  scanf("%d", &n);
  for(int i = 0; i <= n; i++) g[i].clear();
  for(int i = 0; i < n - 1; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    g[u].push_back(v);
    g[v].push_back(u);
  }

  dfs(-1, 1);
  set<pair<int, int>> s;
  for(int i = 1; i <= n; i++) s.insert({h[i], i});
  vector<int> ans;
  int bridge = n;
  while(s.size() > 0) {
    auto it = s.end();
    it--;
    int u = it -> second;
    while(u != -1) {
      s.erase({h[u], u});
      int nxt = -1;
      for(int v : g[u]) {
        if(h[u] == h[v] + 1) {
          nxt = v;
          break;
        }
      }
      bridge--;
      u = nxt;
    }
    ans.push_back(bridge);
  }

  int t = 0;
  for(int i = 0; i < ans.size(); i += 2) {
    t++;
    printf("%d ", ans[i]);
  }
  for(int i = 0; i < n - t - 1; i++) {
    printf("0 ");
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
