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

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}


const int N = 2e5 + 10;
int a[N];
vector<int> g[N];
vector<int> base[N], lbase[N], rbase[N];

int ids[N], rids[N], sz[N], d[N];
int f[N][19], b[N][31], lb[N][31], rb[N][31];

int id = 0;
int n;

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

void to(int& u, int d) {
  for(int i = 30; i >= 0; i--) {
    if(d & (1 << i)) u = f[u][i];
  }
}

void add(int u, int x, int b[N][31], vector<int>& base) {
  int oldx = x;
  for(int i = 30; i >= 0; i--) {
    if(x & (1 << i)) {
      if(b[u][i]) x ^= b[u][i];
      else {
        b[u][i] = x;
        base.push_back(oldx);
        break;
      }
    }
  }
}

void add1(vector<int>& ba, int x) {
  for(int i = 30; i >= 0; i--) {
    if(x & (1 << i)) {
      if(ba[i]) x ^= ba[i];
      else {
        ba[i] = x;
        return;
      }
    }
  }
}

void dfs(int pa, int u, int h) {
  d[u] = h;
  sz[u] = 1;
  ids[u] = id;
  rids[id] = u;
  id++;
  f[u][0] = pa;
  add(u, a[u], b, base[u]);
  for(int v : g[u]) {
    if(v == pa) continue;
    dfs(u, v, h + 1);
    sz[u] += sz[v];
    for(int bit : base[v]) {
      add(u, bit, b, base[u]);
    }
  }
}

void solve() {
  scanf("%d", &n);
  //reset
  id = 0;
  for(int i = 0; i <= n; i++) {
    g[i].clear();
    base[i].clear();
    for(int j = 0; j < 19; j++) f[i][j] = -1;
    for(int j = 0; j < 31; j++) b[i][j] = lb[i][j] = rb[i][j] = 0;
  }
  

  for(int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
  }
  for(int i = 0; i < n - 1; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    g[u].push_back(v);
    g[v].push_back(u);
  }

  dfs(-1, 1, 0);
  for(int i = 1; i < 19; i++) {
    for(int j = 1; j <= n; j++) {
      if(f[j][i - 1] != -1) {
        f[j][i] = f[f[j][i - 1]][i - 1];
      }
    }
  }



  for(int i = 0; i < id; i++) {
    lbase[i].clear();
    int u = rids[i];
    add(i, a[u], lb, lbase[i]);
    if(i - 1 >= 0) {
      for(int x : lbase[i - 1]) {
        add(i, x, lb, lbase[i]);
      }
    }
  }

  for(int i = id - 1; i >= 0; i--) {
    rbase[i].clear();
    int u = rids[i];
    add(i, a[u], rb, rbase[i]);
    if(i + 1 < id) {
      for(int x : rbase[i + 1]) {
        add(i, x, rb, rbase[i]);
      }
    }
  }

  int m;
  scanf("%d", &m);
  while(m--) {
    int r, v;
    scanf("%d%d", &r, &v);
    int lca = LCA(r, v);
    int ans = 0;
    //cout << "LCA " << r << " " << v << " " << lca << endl;
    if(r == v) {
      v = 1;
      for(int i = 30; i >= 0; i--) {
        if(b[v][i] && (ans ^ b[v][i]) > ans) ans ^= b[v][i];
      }
      printf("%d\n", ans);
      continue;
    }
    
    if(lca == r || lca != v) { //v inside r
      for(int i = 30; i >= 0; i--) {
        if(b[v][i] && (ans ^ b[v][i]) > ans) ans ^= b[v][i];
      }
    } else {
      to(r, d[r] - d[lca] - 1);
      int left = ids[r], right = left + sz[r] - 1;
      //cout << r <<"  " << left << " " << right << endl;
      vector<int> ba(31);
      if(left - 1 >= 0) {
        for(int x : lbase[left - 1]) add1(ba, x);
      }
      if(right + 1 < id) {
        for(int x : rbase[right + 1]) add1(ba, x);
      }
      for(int i = 30; i >= 0; i--) {
        if(ba[i] && (ans ^ ba[i]) > ans) ans ^= ba[i];
      }
    }
    printf("%d\n", ans);
  }
}


int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
