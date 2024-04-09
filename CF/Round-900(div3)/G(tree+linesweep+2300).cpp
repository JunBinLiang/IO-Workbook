#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <map>
#include <unordered_set>
#include <string.h>

using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define ve vector

const int N = 2e5 + 10;
int a[N], d[N], c[N], llca[N], sums[N][31];
vector<int> g[N];
vector<pair<int, int>> lines[N];
pair<int, int> q[N];
int f[N][18], s[N][18];
int LCA(int x, int y) {
  if(d[x] < d[y]){
    return LCA(y, x);
  }

  for(int i = 17; i>=0; i--) {
    if(f[x][i] != -1 && d[f[x][i]] >= d[y]) {
      x = f[x][i];
    }
  }
  if(x == y) return x;
  for(int i = 17; i>=0; i--) {
    if(f[x][i] != f[y][i]) {                    
      x = f[x][i];
      y = f[y][i];
    }
  }
  return f[x][0];
}

void dfs(int pa, int u, int h) {
  d[u] = h;
  f[u][0] = pa;
  for(int i = 0; i < 31; i++) {
      if(a[u] & (1 << i)) sums[u][i] = 1;
      else sums[u][i] = 0;
      if(pa != -1) sums[u][i] += sums[pa][i];
  }
  for(int& v : g[u]) {
    if(v == pa) continue;
    dfs(u, v, h + 1);
  }
}

pair<int, int> jump(int u, int& lca, int& b, int& sum, bool early) {
  pair<int, int> ans = {-1, -1};
  int curu = u, curs = 0;
  for(int i = 17; i >= 0 && curu != -1; i--) {
    if(d[curu] - d[lca] < (1 << i)) {
      continue;
    }
    if(s[curu][i] == 0) {
      curu = f[curu][i];
      curu = f[curu][0];
    } else {
      ans.first = f[curu][i];
    }
  } 
  if(curu != -1 && a[curu] & (1 << b)) ans.first = curu;
  if(early) return ans;

  curu = u; curs = 0; 
  for(int i = 17; i >= 0 && curu != -1; i--) {
    if(d[curu] - d[lca] < (1 << i)) {
      continue;
    }
    if(curs + s[curu][i] < sum) {
      curs += s[curu][i];
      curu = f[curu][i];
      curu = f[curu][0];
    } else {
      ans.second = f[curu][i];
    }
  }
  if(curu != -1 && a[curu] & (1 << b) && curs + 1 == sum) ans.second = curu;
  return ans;
}

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
} tr;

void solve() {
  int n, m;
  scanf("%d", &n);
  for(int i = 0; i <= n; i++) g[i].clear();

  for(int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
  }
  for(int i = 0; i < n - 1; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    g[u].push_back(v); g[v].push_back(u);
  }

  for(int i = 0; i < 18; i++) {
    for(int j = 1; j <= n; j++) f[j][i] = -1;
  }

  dfs(-1, 1, 0);
  for(int i = 1; i < 18; i++) {
    for(int j = 1; j <= n; j++) {
      if(f[j][i - 1] != -1) {
        f[j][i] = f[f[j][i - 1]][i - 1];
      }
    }
  }

  scanf("%d", &m);
  for(int i = 0; i < m; i++) lines[i].clear();

  vector<int> ans(m);
  for(int i = 0; i < m; i++) {
    scanf("%d%d", &q[i].first, &q[i].second);
    if(d[q[i].first] < d[q[i].second]) swap(q[i].first, q[i].second);
    llca[i] = LCA(q[i].first, q[i].second);
    int u = q[i].first, v = q[i].second;
    c[i] = (d[u] - d[llca[i]] + 1) + (d[v] - d[llca[i]] + 1) - 1;
  }
  
  for(int b = 30; b >= 0; b--) {
    for(int j = 1; j <= n; j++) {
      if(a[j] & (1 << b)) {
        s[j][0] = 1;
      } else {
        s[j][0] = 0;
      }
    }
    
    for(int j = 2; j <= n; j++) {
       if(a[f[j][0]] & (1 << b)) {
          s[j][0]++;
      } 
    }

    for(int i = 1; i < 18; i++) {
      for(int j = 1; j <= n; j++) {
        if(f[j][i - 1] != -1) {
          int t = 0;
          if(a[f[j][i - 1]] & (1 << b)) t = 1;
          s[j][i] = s[j][i - 1] + s[f[j][i - 1]][i - 1] - t;
        }
      }
    }
    
    for(int i = 0; i < m; i++) {
      int& u = q[i].first, v = q[i].second;
      int& lca = llca[i];
      int s1 = sums[u][b] - sums[lca][b];
      int s2 = sums[v][b] - sums[lca][b];
      int sub = 0;
      if(a[lca] & (1 << b)) sub = 1;
      s1 += sub;
      s2 += sub;
      if(s1 == 0 && s2 == 0) continue;
      int l = -1, r = -1;
      if(s1 == 0) {
        pair<int, int> p2 = jump(v, lca, b, s2, false);
        l = c[i] - (d[v] - d[p2.second] + 1);
        r = c[i] - (d[v] - d[p2.first] + 1);
      } else if(s2 == 0) {
        pair<int, int> p1 = jump(u, lca, b, s1, false);
        l = d[u] - d[p1.first];
        r = d[u] - d[p1.second];
      } else {
        pair<int, int> p1 = jump(u, lca, b, s1, true);
        pair<int, int> p2 = jump(v, lca, b, s2, true);
        l = d[u] - d[p1.first];
        r = c[i] - (d[v] - d[p2.first] + 1);
      }
      lines[i].push_back({l, r});
    }
  }

  //if(n == 200000 && a[1] == 35 && a[2] == 5) return;
  tr.init(n + 5);
  for(int i = 0; i < m; i++) {
    int u = q[i].first, v = q[i].second;
    if(d[u] < d[v]) swap(u, v);

    for(auto& p : lines[i]) {
      int l = p.first, r = p.second;
      tr.update(l, 1);
      tr.update(r + 1, -1);
    }

    int mx = 0;
    for(auto& p : lines[i]) {
      int l = p.first, r = p.second;
      mx = max(mx, tr.query(0, l));
      mx = max(mx, tr.query(0, r));
    }

    //reset
    for(auto& p : lines[i]) {
      int l = p.first, r = p.second;
      tr.update(l, -1);
      tr.update(r + 1, 1);
    }
    ans[i] = mx * 2 + (lines[i].size() - mx);
  }

  for(int& x : ans) printf("%d ", x);
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
