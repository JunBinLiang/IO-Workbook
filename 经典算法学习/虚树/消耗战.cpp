//https://vjudge.net/problem/%E6%B4%9B%E8%B0%B7-P2495
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
  const int SIZE = 3e5 + 10;
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

  const int N = 3e5 + 10, M = 19;
  int d[N], dfn[N], f[N][M], w[N][M], id = 0;
  int stk[N];
  vector<int> g[N];

  void init() {
    memset(f, -1, sizeof f);
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            w[i][j] = 1e9;
        }
    }
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
          w[j][i] = min(w[j][i - 1], w[f[j][i - 1]][i - 1]);
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

  int jump(int u, int d) {
    int ans = 1e9;
    for(int i = M - 1; i >= 0; i--) {
      if(d & (1 << i)) {
        ans = min(ans, w[u][i]);
        u = f[u][i];
      }
    }
    return ans;
  }
}


const int N = 3e5 + 10;
const ll INF = 1e16;
ll d[N];
bool critical[N];
vector<pair<int, int>> g[N];
ll dp[N][2];

void dfs1(int pa, int u) {
  for(auto& p : g[u]) {
    int v = p.first;
    if(v == pa) continue;
    VirtualTree :: w[v][0] = p.second;
    dfs1(u, v);
  }
}

void dfs2(int pa, int u) {
  dp[u][0] = dp[u][1] = INF;
  if(VirtualTree :: graph.g[u].size() == 1 && pa != -1) {
    if(critical[u]) {
      dp[u][1] = 0;
    } else {
      dp[u][0] = 0;
    }
    return;
  }

  
  ll s1 = 0; ll s2 = 0;
  vector<pair<ll, ll>> a;
  for(int v : VirtualTree :: graph.g[u]) {
    if(pa == v) continue;
    dfs2(u, v);
    int w = VirtualTree :: jump(v, VirtualTree :: d[v] - VirtualTree :: d[u]);
    //cout << u << "  " << v << " " << w << endl;
    s1 += min(dp[v][0], dp[v][1] + w);
    s1 = min(s1, INF);
    
    s2 += min(dp[v][0], dp[v][1]);
    s2 = min(s2, INF);
    a.push_back({dp[v][0], dp[v][1]});
  }
  if(critical[u]) {
    dp[u][1] = s2;
  } else {
    dp[u][0] = s1;
    vector<ll> l(a.size()), r(a.size());
    ll s = 0;
    for(int i = 0; i < a.size(); i++) {
      s += min(a[i].first, a[i].second);
      s = min(s, INF);
      l[i] = s;
    }
    s = 0;
    for(int i = a.size() - 1; i >= 0; i--) {
      s += min(a[i].first, a[i].second);
      s = min(s, INF);
      r[i] = s;
    }
    
    for(int i = 0; i < a.size(); i++) {
      ll c = a[i].second;
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
  for(int i = 0; i < n - 1; i++) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    g[u].push_back({v, w});
    g[v].push_back({u, w});
    VirtualTree :: add(u, v);
  }

  VirtualTree :: init();
  memset(critical, 0, sizeof critical);
  dfs1(-1, 1);
  VirtualTree :: preBuild(n);
  
  int m;
  scanf("%d", &m);
  while(m--) {
    int size;
    scanf("%d", &size);
    vector<int> a(size);
    for(int i = 0; i < size; i++) {
      scanf("%d", &a[i]);
      critical[a[i]] = true;
    }

    VirtualTree :: graph.clear();
    VirtualTree :: build(a);
    dfs2(-1, 1);
    cout << dp[1][0] << endl;
    for(int i = 0; i < size; i++) {
      critical[a[i]] = false;
    }
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
