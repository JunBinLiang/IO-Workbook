#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <map>
#include <set>
#include <string.h>

using namespace std;  
using ll = long long;

const int N = 5e4 + 10, INF = 1e9;
char s[N];
bool vir[N * 2];
vector<pair<int, int>> g[N * 2];
int n, m;

int node(int c1, int c2) {
  return c1 * 26 + c2;
}

struct Query {
  int u, v, ans;
} qu[N];

void solve() {
  scanf("%s", s);
  n = strlen(s);
  scanf("%d", &m);

  vector<int> a;
  for(int i = 1; i < n; i++) {
    int c1 = s[i - 1] - 'a', c2 = s[i] - 'a';
    a.push_back(node(c1, c2));
  }

  for(int i = 0; i < a.size(); i++) {
    if(i > 0) {
      g[i].push_back({i - 1, 1});
      g[i - 1].push_back({i, 1});
    }
    g[i].push_back({n + a[i], 0});
    g[n + a[i]].push_back({i, 1});
    vir[n + a[i]] = true;
  }

  for(int i = 0; i < m; i++) {
    scanf("%d%d", &qu[i].u, &qu[i].v);
    qu[i].ans = 0;
    qu[i].ans = abs(qu[i].u - qu[i].v);
    qu[i].u--;
    qu[i].v--;
  }
  
  for(int i = 0; i < 2 * N; i++) {
    if(!vir[i]) continue;
    vector<int> d(N * 2, INF);
    deque<int> q;
    d[i] = 0;
    q.push_back(i);
    while(q.size() > 0) {
      int u = q.front();
      q.pop_front();
      for(auto& p : g[u]) {
        int v = p.first, w = p.second;
        if(d[u] + w < d[v]) {
          d[v] = d[u] + w;
          if(w == 1) q.push_back(v);
          else q.push_front(v);
        }
      }
    }

    for(int j = 0; j < m; j++) {
      qu[j].ans = min(qu[j].ans, d[qu[j].u] + d[qu[j].v] - 1);
    }
  }

  for(int i = 0; i < m; i++) printf("%d\n", qu[i].ans);
}

int main(){
  int t = 1;
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
