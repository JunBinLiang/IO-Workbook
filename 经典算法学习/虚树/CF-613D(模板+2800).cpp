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

namespace VirtualTree {
  const int SIZE = 1e5 + 10;
  struct Graph { //general graph
    vector<int> g[SIZE];
    vector<pair<int, int>> edges;
    void add(int u, int v) {
      g[u].push_back(v);
      g[v].push_back(u);
      edges.push_back({u, v});
    }

    void clear() {
      for(auto& e : edges) {
        g[e.first].clear();
        g[e.second].clear();
      }
      edges.clear();
    }
  } graph;

  const int N = 1e5 + 10, M = 19;
  int d[N], dfn[N], f[N][M], id = 0;
  int stk[N];
  vector<int> g[N];

  void init() {
    memset(f, -1, sizeof f);
  }

  bool comp(int x, int y) {
    return dfn[x] < dfn[y];
  }

  void add(int u, int v) {
    g[u].push_back(v);
    g[v].push_back(u);
  }

  void dfs(int pa, int root, int dep) {
    d[root] = dep;
    dfn[root] = id++;
    f[root][0] = pa;     
    for(int& nxt : g[root]) {
      if(nxt != pa) {
        dfs(root, nxt, dep + 1);
      }
    }
  }

  int LCA(int x,int y) {
    if(d[x] < d[y]){
      return LCA(y,x);
    }
    for(int i = M - 1; i >= 0; i--) {
      if(f[x][i] != -1 && d[f[x][i]] >= d[y]) {
        x = f[x][i];
      }
    }
    if(x == y) return x;
    for(int i = M - 1; i >= 0; i--) {
      if(f[x][i] != f[y][i]) {                    
        x = f[x][i];
        y = f[y][i];
      }
    }
    return f[x][0];
  }

  void preBuild(int n) {
    dfs(-1, 1, 0);
    for(int i = 1; i < M; i++) {
      for(int j = 1; j <= n; j++) {
        if(f[j][i - 1] != -1) {
            f[j][i] = f[f[j][i - 1]][i - 1];
        }
      }
    }
  }
  
  //use stack to build the virtual tree:https://oi-wiki.org/graph/virtual-tree/#%E5%BC%95%E5%85%A5
  void build(vector<int>& a) {
    sort(a.begin(), a.end(), comp);
    int top = 0;
    stk[ top = 1 ] = 1;
    for(int i = 0; i < a.size(); i++) {
      int u = a[i];
      if(u == 1) continue;
      int lca = LCA(u, stk[top]);
      if(lca != stk[top]) {
        while(dfn[lca] < dfn[stk[top - 1] ]) {
          graph.add(stk[top - 1], stk[top]);
          top --;
        }
        if(dfn[lca] > dfn[stk[top - 1] ]) graph.add(lca, stk[top]), stk[top] = lca;
        else if(dfn[lca] == dfn[stk[top - 1] ]) {
            graph.add(lca, stk[top]), top --;
        }
      }
      stk[++ top] = u;
    }
    while(top > 1) {
      graph.add(stk[top - 1], stk[top]);
      top--;
    }
  }
}

const int N = 1e5 + 10, INF = 1e9;
bool critical[N];
int dp[N][2];
bool noCut = false;
void dfs(int pa, int u) {
  auto& g = VirtualTree :: graph.g;
  dp[u][0] = dp[u][1] = INF;
  if(g[u].size() == 1 && pa != -1) {
    if(critical[u]) {
      dp[u][1] = 0;
    } else {
      dp[u][0] = 0;
    }
    return;
  }

  int s1 = 0, s2 = 0;
  vector<pair<int, int>> a;
  for(int v : g[u]) {
    if(v == pa) continue;
    dfs(u, v);

    if(critical[v] && critical[u] && VirtualTree :: f[v][0] == u) {
      noCut = true;
      return;
    }

    s1 += (min(1 + dp[v][1], dp[v][0]));
    s1 = min(s1, INF);
    s2 += min(dp[v][0], dp[v][1]);
    s2 = min(s2, INF);
    a.push_back({dp[v][0], dp[v][1]});
  }
  
  if(critical[u]) {
    dp[u][1] = s1;
  } else {
    dp[u][0] = s1;
    dp[u][0] = min(dp[u][0], 1 + s2);

    vector<int> l(a.size()), r(a.size());
    int s = 0;
    for(int i = 0; i < a.size(); i++) {
      s += min(a[i].first, 1 + a[i].second);
      s = min(s, INF);
      l[i] = s;
    }
    s = 0;
    for(int i = a.size() - 1; i >= 0; i--) {
      s += min(a[i].first, 1 + a[i].second);
      s = min(s, INF);
      r[i] = s;
    }
    
    for(int i = 0; i < a.size(); i++) {
      int c = a[i].second;
      if(i > 0) {
        c += l[i - 1];
        c = min(c, INF);
      }
      if(i + 1 < a.size()) {
        c += r[i + 1];
        c = min(c, INF);
      }
      dp[u][1] = min(dp[u][1], c);
    }
  }
}


void solve() {
  int n;
  scanf("%d", &n);
  for(int i = 0; i <= n; i++) {
    critical[i] = false;
    dp[i][0] = dp[i][1] = INF;
  }

  VirtualTree :: init();

  for(int i = 0; i < n - 1; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    VirtualTree :: add(u, v);
  }
  VirtualTree :: preBuild(n);

  int m;
  scanf("%d", &m);
  while(m--) {
    //critical points
    int size;
    scanf("%d", &size);
    vector<int> a(size);
    for(int i = 0; i < a.size(); i++) {
      scanf("%d", &a[i]);
      critical[a[i]] = true;
    }
    VirtualTree :: graph.clear();
    VirtualTree :: build(a);
    noCut = false;
    dfs(-1, 1);
    for(int i = 0; i < a.size(); i++) {
      critical[a[i]] = false;
    }
    if(noCut) {
      printf("-1\n");
      continue;
    }
    printf("%d \n", min(dp[1][0], dp[1][1]));
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
