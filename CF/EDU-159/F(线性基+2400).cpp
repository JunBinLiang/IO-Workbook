#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <string.h>

using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define ve vector

const int N = 2e5 + 10;
int a[N];
vector<int> g[N];
int f[N][19], d[N];
int LCA(int x, int y) {
  if(d[x] < d[y]){
    return LCA(y, x);
  }
 
  for(int i = 18; i>=0; i--) {
    if(f[x][i] != -1 && d[f[x][i]] >= d[y]) {
      x = f[x][i];
    }
  }
  if(x == y) return x;
  for(int i = 18; i>=0; i--) {
    if(f[x][i] != f[y][i]) {                    
      x = f[x][i];
      y = f[y][i];
    }
  }
  return f[x][0];
}

int b[N][21];
vector<int> ver[N];
bool add(int u, int x) {
  for(int i = 20; i >= 0; i--) {
    if(x & (1 << i)) {
      if(b[u][i]) x ^= b[u][i];
      else {
        b[u][i] = x;
        return true;
      }
    }
  }
  return false;
}

void add1(vector<int>& base, int x) {
  for(int i = 20; i >= 0; i--) {
    if(x & (1 << i)) {
      if(base[i]) x ^= base[i];
      else {
        base[i] = x;
        return;
      }
    }
  }
}

void dfs(int pa, int u, int h) {
  f[u][0] = pa;
  d[u] = h;
  if(add(u, a[u])) {
    ver[u].push_back(u);
  }
  if(pa != -1) {
    for(int v : ver[pa]) {
        if(add(u, a[v])) {
            ver[u].push_back(v);
        }
    }
  }
  
  for(int v : g[u]) {
    if(v != pa) dfs(u, v, h + 1);
  }
}


void solve() {
  int n, m;
  scanf("%d", &n);
  for(int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
  }

  for(int i = 0; i < n - 1; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    g[u].push_back(v);
    g[v].push_back(u);
  }

  memset(b, 0, sizeof b);
  memset(f, -1, sizeof f);
  dfs(-1, 1, 0);
  for(int i = 1; i < 19; i++) {
    for(int j = 1; j <= n; j++) {
      if(f[j][i - 1] != -1) {
        f[j][i] = f[f[j][i - 1]][i - 1];
      }
    }
  }


  scanf("%d", &m);
  while(m--) {
    int u, v, k;
    scanf("%d%d%d", &u, &v, &k);
    if(d[u] < d[v]) swap(u, v);
    int lca = LCA(u, v);

    vector<int> base(21);
    for(int node : ver[u]) {
      if(d[node] >= d[lca]) {
        add1(base, a[node]);
      }
    }
    for(int node : ver[v]) {
      if(d[node] >= d[lca]) {
        add1(base, a[node]);
      }
    }
    
    int count = 0;
    for(int i = 0; i < base.size(); i++) {
        if(base[i]) count++;
    }
    
    if(d[u] - d[lca] + 1 + d[v] - d[lca] + 1 - 1 == count && k == 0) {
        printf("YES\n");
        continue;
    }
    
    for(int i = base.size() - 1; i >= 0; i--) {
      if(k & (1 << i)) k ^= base[i];
    }
    if(k == 0) printf("YES\n");
    else printf("NO\n");
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
