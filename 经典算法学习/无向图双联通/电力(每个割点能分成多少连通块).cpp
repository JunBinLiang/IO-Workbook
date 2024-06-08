//https://vjudge.net/problem/LibreOJ-10103
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
  const int N = 1e4 + 100;
  int dfn[N], low[N], t = 0;
  vector<int> g[N];
  int ans;

  void init(int n) {
    t = 0;
    ans = 0;
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
    int count = 0;
    for(int to : g[u]) {
      if(to == pa) continue; //不能直接用parent
      if(dfn[to]) {
        low[u] = min(low[u], dfn[to]);
      } else {
        tarjan(u, to);
        low[u] = min(low[u], low[to]);
        if (low[to] >= dfn[u]) {
          count++;
        }
        
      }
    }
    if (pa) { //root
      count++;
    }
    ans = max(ans, count);
  }
}

bool solve() {
  int n, m;
  scanf("%d%d", &n, &m);
  if(n == 0 && m == 0) {
    return false;
  }
  CutPoint :: init(n);
  for(int i = 0; i < m; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    u++; v++;
    CutPoint :: add(u, v);
  }

  int count = 0;
  for(int i = 1; i <= n; i++) {
    if(!CutPoint :: dfn[i]) {
      CutPoint :: tarjan(0, i);
      count++;
    }
  }

  //其中一个进行分裂所以要 - 1
  cout << (count - 1) + CutPoint :: ans << endl;
  return true;
}

int main(){
  int t = 1;
  //cin >> t;
  while(solve()) {}
  return 0;
}
