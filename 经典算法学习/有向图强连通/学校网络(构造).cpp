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

const int N = 1e5 + 10;
namespace DirectGraphSCC {
  vector<int> g[N];
  vector<int> stk;
  bool inStk[N];
  int dfn[N], low[N], t = 0, scc = 0;
  int ids[N], sz[N];
  
  void init(int n) {
    t = 0;
    scc = 0;
    for(int i = 0; i <= n; i++) {
      g[i].clear();
      dfn[i] = low[i] = 0;
      inStk[i] = false;
    }
  }
  
  void add(int u, int v) {
    g[u].push_back(v);
  }

  void tarjan(int u) {
    dfn[u] = low[u] = ++t;
    stk.push_back(u);
    inStk[u] = true;
    for(int v : g[u]) {
      if(!dfn[v]) {
        tarjan(v);
        low[u] = min(low[u], low[v]);
      } else if(inStk[v]) {
        low[u] = min(low[u], dfn[v]);
      }
    }

    if(dfn[u] == low[u]) { //u 是强联通最高点
        int y;
        do {
            y = stk.back(); stk.pop_back();
            inStk[y] = false;
            ids[y] = scc;
            sz[scc] ++ ;
        } while (y != u);
        scc++;
    }
  }
}

void solve() {
  int n;
  scanf("%d", &n);
  DirectGraphSCC :: init(n);
  for(int u = 1; u <= n; u++) {
    while(true) {
      int v;
      scanf("%d", &v);
      if(!v) break;
      DirectGraphSCC :: add(u, v);
    }
  }

  for(int i = 1; i <= n; i++) {
    if(!DirectGraphSCC :: dfn[i]) {
      DirectGraphSCC :: tarjan(i);
    }
  }

  vector<int> in(DirectGraphSCC :: scc), out(DirectGraphSCC :: scc);
  for(int u = 1; u <= n; u++) {
    for(int v : DirectGraphSCC :: g[u]) {
      if(DirectGraphSCC :: ids[u] != DirectGraphSCC :: ids[v]) {
        in[DirectGraphSCC :: ids[v]]++;
        out[DirectGraphSCC :: ids[u]]++;
      }
    }
  }

  int ans1 = 0, ans2 = 0;
  for(int i = 0; i < DirectGraphSCC :: scc; i++) {
    if(!in[i]) {
      ans1++;
    }
    if(!out[i]) {
      ans2++;
    }
  }

  cout << ans1 << endl;
  if(DirectGraphSCC :: scc == 1) cout << 0 << endl;
  else {
    cout << max(ans1, ans2) << endl;
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
