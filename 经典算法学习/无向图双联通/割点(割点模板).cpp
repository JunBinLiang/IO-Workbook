//https://vjudge.net/problem/%E6%B4%9B%E8%B0%B7-P3388
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

//https://tom0727.github.io/post/041-%E5%89%B2%E7%82%B9-%E6%A1%A5-bcc/
//https://oi-wiki.org/graph/cut/
namespace CutPoint {
  const int N = 1e5 + 10;
  int dfn[N], low[N], t = 0;
  vector<int> g[N];
  vector<int> ans;

  void init(int n) {
    t = 0;
    for(int i = 0; i <= n; i++) {
      dfn[i] = low[i] = 0;
      g[i].clear();
    }
  }

  void add(int u, int v) {
    g[u].push_back(v);
    g[v].push_back(u);
  }

  void tarjan(int pa, int u) {
    dfn[u] = low[u] = ++t;
    int child = 0;
    int cut = 0;
    for(int to : g[u]) {
      if(to == pa) continue; //不能直接用parent
      if(dfn[to]) {
        low[u] = min(low[u], dfn[to]);
      } else {
        tarjan(u, to);
        child++;
        low[u] = min(low[u], low[to]);
        if (pa && low[to] >= dfn[u]) cut = 1;  
        // 如果u不是根节点，且存在 direct child使得 low[to] >= dfn[u]，则u是割点
      }
    }
    if (!pa && child >= 2) cut = 1;  // 如果为根节点，且有 >= 2个子树
    if (cut) ans.push_back(u);
  }
}

void solve() {
  int n, m;
  scanf("%d%d", &n, &m);
  CutPoint :: init(n);
  for(int i = 0; i < m; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    CutPoint :: add(u, v);
  }

  for(int i = 1; i <= n; i++) {
    if(!CutPoint :: dfn[i]) {
      CutPoint :: tarjan(0, i);
    }
  }

  sort(CutPoint :: ans.begin(), CutPoint :: ans.end());
  cout << CutPoint :: ans.size() << endl;
  for(int x : CutPoint :: ans) {
    cout << x << " ";
  }
  cout << endl;
}

int main(){
  int t = 1;
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
