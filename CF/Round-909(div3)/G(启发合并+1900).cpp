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


const int N = 1e5 + 10;
vector<int> g[N];
set<int> p[N];
int pos[N];
bool ans[N];
struct Q {
  int l, r, i;
};
vector<Q> q[N];

void dfs(int pa, int u) {
  p[u].insert(pos[u]);
  for(int v : g[u]) {
    if(v == pa) {
      continue;
    }
    dfs(u, v);
    if(p[u].size() < p[v].size()) swap(p[u], p[v]);
    for(auto x : p[v]) p[u].insert(x);
  }

  auto& s = p[u];
 
  for(auto& query : q[u]) {
    int L = query.l, R = query.r, i = query.i;
    auto it = s.upper_bound(L - 1);
    if(it != s.end() && (*it) <= R) {
        ans[i] = true;
    }
  }
}

void solve() {
  int n, m;
  scanf("%d%d", &n, &m);
  vector<int> per(n + 1);
  for(int i = 0; i <= n; i++){
       g[i].clear();
       p[i].clear();
       q[i].clear();
  }
  for(int i = 0; i <= m; i++) ans[i] = false;

  for(int i = 0; i < n - 1; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    g[u].push_back(v);
    g[v].push_back(u);
  }
  for(int i = 1; i <= n; i++) {
    scanf("%d", &per[i]);
    pos[per[i]] = i;
  }

  for(int i = 0; i < m; i++) {
    int l, r, x;
    scanf("%d%d%d", &l, &r, &x);
    q[x].push_back({l, r, i});
  }
  dfs(-1, 1);


  for(int i = 0; i < m; i++) {
    if(ans[i]) printf("YES\n");
    else printf("NO\n");
  }
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
