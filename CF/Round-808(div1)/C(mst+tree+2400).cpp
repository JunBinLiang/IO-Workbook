#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <set>
#include <string.h>

using namespace std;  
using ll = long long;

const int N = 2e5 + 10;
vector<int> g[N];
int p[N];
bool mst[N];

int d[N], f[N][20];
int sz[N], ids[N], id = 0;

const int SIZE = 200000 + 100;
struct Fenwick {
  int tree[SIZE];
  void init(int n) {
    for(int i = 0; i <= n + 1; i++) tree[i] = 0;
  }

  void update(int i, int val) {
    i++;
    while(i < SIZE){
      tree[i] += val;
      i += (i & -i);
    }
  }

  int pre(int i) {
    int sum = 0;
    while(i>0){
      sum += tree[i];
      i -= ( i & -i);
    }
    return sum;
  }
  int query(int i, int j) {
      return pre(j + 1) - pre(i);
  }
} tr1;


struct Edge {
  int u, v;
} e[N];

int find(int u) {
  return p[u] == u ? u : p[u] = find(p[u]);
}

int LCA(int x, int y) {
  if(d[x] < d[y]){
    return LCA(y,x);
  }

  for(int i = 19; i >= 0; i--) {
    if(f[x][i] != -1 && d[f[x][i]] >= d[y]) {
      x = f[x][i];
    }
  }
  
  if(x == y) return x;
  for(int i = 19; i >= 0; i--) {
    if(f[x][i] != f[y][i]) {                    
      x = f[x][i];
      y = f[y][i];
    }
  }
  return f[x][0];
}

int jump(int u, int k) {
  for(int i = 19; i >= 0; i--) {
    if(k & (1 << i)) u = f[u][i];
  }
  return u;
}

void dfs(int pa, int u, int h) {
  d[u] = h;
  f[u][0] = pa;
  sz[u] = 1;
  ids[u] = id++;
  for(int v : g[u]) {
    if(v == pa) continue;
    dfs(u, v, h + 1);
    sz[u] += sz[v];
  }
}

void solve() {
  int n, m;
  scanf("%d%d", &n, &m);
  
  //init
  memset(f, -1, sizeof f);
  for(int i = 1; i <= n; i++) p[i] = i;

  for(int i = 1; i <= m; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    e[i] = {u, v};
    int r1 = find(u), r2 = find(v);
    if(r1 != r2) {
      p[r1] = r2;
      mst[i] = true;
      g[u].push_back(v);
      g[v].push_back(u);
    }
  }

  
  dfs(-1, 1, 0);
  for(int j = 1; j < 20; j++) {
    for(int i = 1; i <= n; i++) {
      if(f[i][j - 1] != -1) {
        f[i][j] = f[f[i][j - 1]][j - 1];
      }
    }
  }
  
  tr1.init(n + 5);
  for(int i = 1; i <= m; i++) {
    if(mst[i]) continue;
    int u = e[i].u, v = e[i].v;
    if(d[u] < d[v]) swap(u, v);
    int lca = LCA(u, v);
    int l1 = ids[u], r1 = l1 + sz[u] - 1;
    int l2 = ids[v], r2 = l2 + sz[v] - 1;
    if(lca == v) {
      int node = jump(u, d[u] - d[v] - 1);
      l2 = ids[node];
      r2 = l2 + sz[node] - 1;
      tr1.update(l2, 1);
      tr1.update(r2 + 1, -1);
      tr1.update(l1, -1);
      tr1.update(r1 + 1, 1);
    } else {
      //set all fail
      tr1.update(0, 1);
      tr1.update(n, -1);
      tr1.update(l1, -1);
      tr1.update(r1 + 1, 1);
      tr1.update(l2, -1);
      tr1.update(r2 + 1, 1);
    }
  }

  for(int i = 1; i <= n; i++) {
    int count = tr1.query(0, ids[i]);
    if(count != 0) printf("0");
    else printf("1");
  }
  printf("\n");
}

int main(){
  int t = 1;
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}

