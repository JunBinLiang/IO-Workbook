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

const int N = 2e5 + 10, M = 20;
int d[N], a[N], f[N][M];
bool ok = false;

struct Node {
  int lmax, lmin, rmax, rmin, mx, mn, s;
} spa[N][M];

int LCA(int x,int y) {
  if(d[x] < d[y]){
    return LCA(y,x);
  }
  for(int i = M - 1; i >= 0; i--) {
    if(f[x][i] != -1 && f[f[x][i]][1] != -1 && d[f[f[x][i]][1]] >= d[y]) {
      x = f[f[x][i]][1];
    }
  }
  if(x == y) return x;
  for(int i = M - 1; i >= 0; i--) {
    if(f[x][i] != -1 && f[y][i] != -1 && f[f[x][i]][1] != f[f[y][i]][1]) {                    
      x = f[f[x][i]][1];
      y = f[f[y][i]][1];
    }
  }
  return f[x][1];
}

Node merge(Node& node1, Node& node2) {
  Node ans = {};
  ans.s = node1.s + node2.s;
  ans.lmin = min(node1.lmin, node1.s + node2.lmin);
  ans.lmax = max(node1.lmax, node1.s + node2.lmax);
  ans.rmin = min(node2.rmin, node2.s + node1.rmin);
  ans.rmax = max(node2.rmax, node2.s + node1.rmax);
  
  ans.mn = min(node1.mn, node2.mn);
  ans.mx = max(node1.mx, node2.mx);
  ans.mn = min(ans.mn, min(ans.lmin, ans.rmin));
  ans.mx = max(ans.mx, max(ans.lmax, ans.rmax));
  ans.mn = min(ans.mn, ans.s);
  ans.mx = max(ans.mx, ans.s);
  ans.mn = min(ans.mn, node1.rmin + node2.lmin);
   ans.mx = max(ans.mx, node1.rmax + node2.lmax);
  return ans;
}

int up(int u, int d) {
  int ans = u;
  d--;
  u = f[u][1];
  for(int i = M - 1; i >= 0; i--) {
    if(d >= (1 << i)) {
      d -= (1 << i);
      ans = f[u][i];
      u = f[f[u][i]][1];
    }
  }
  return ans;
}

Node jump(int u, int v, int k) { //jump from u to v
  Node cur = spa[u][0]; 
  int mx = cur.mx, mn = cur.mn;
  u = f[u][1];
  for(int i = M - 1; i >= 0 && u != -1; i--) {
    int count = d[u] - d[v] + 1;
    if(count >= (1 << i)) {
      cur = merge(cur, spa[u][i]);
      u = f[f[u][i]][1];
      mx = max(mx, cur.mx);
      mn = min(mn, cur.mn);
    }
  }
  if(k >= mn && k <= mx) {
    ok = true;
  }
  return cur;
}

void solve() {
  int n;
  scanf("%d", &n);
  //reset
  for(int i = 0; i <= n; i++) {
    for(int j = 0; j < M; j++) {
      f[i][j] = -1;
    }
  }

  int id = 1;
  d[1] = 0;
  a[1] = 1;
  
  spa[1][0] = {1, 1, 1, 1, 1, 1, 1};
  f[1][0] = 1;
  f[1][1] = -1;

  for(int i = 0; i < n; i++) {
    char op[2];
    scanf("%s", op);
    if(op[0] == '+') {
      int u, w;
      scanf("%d%d", &u, &w);
      int node = ++id;
      a[node] = w;
      d[node] = d[u] + 1;
   
      f[node][0] = node;
      f[node][1] = u;
      spa[node][0] = {w, w, w, w, w, w, w};
      spa[node][1] = merge(spa[node][0], spa[u][0]);
      for(int j = 1; j < M; j++) {
        if(f[node][j - 1] != -1) {
          int pa = f[f[node][j - 1]][1];
          if(pa != -1 && f[pa][j - 1] != -1) {
            f[node][j] = f[pa][j - 1];
            spa[node][j] = merge(spa[node][j - 1], spa[pa][j - 1]);
          }
        }
      }
    } else {
      int u, v, k;
      scanf("%d%d%d", &u, &v, &k);
      if(d[u] < d[v]) swap(u, v);
      if(k == 0) {
        printf("YES\n");
        continue;
      }
      if(u == v) {
        if(k == spa[u][0].s) {
          printf("YES\n");
        } else {
          printf("NO\n");
        }
        continue;
      }
      ok = false;
      int lca = LCA(u, v);
      Node node1 = jump(u, lca, k);
      if(v == lca) {
        if(ok) printf("YES\n");
        else printf("NO\n");
        continue;
      }
      Node node2 = jump(v, lca, k);
      Node node3 = jump(v, up(v, d[v] - d[lca]), k);
      swap(node3.lmin, node3.rmin);
      swap(node3.lmax, node3.rmax);
      node1 = merge(node1, node3);
      if(k >= node1.mn && k <= node1.mx) {
        ok = true;
      } 
      if(ok) printf("YES\n");
      else printf("NO\n");
    }
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
