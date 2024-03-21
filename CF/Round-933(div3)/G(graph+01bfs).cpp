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
#define FOR(i, a, b) for (int i = a; i < b; ++i)

const int N = 2e5 + 10, INF = 1e9;
vector<int> g[N * 2];

void add(int u, int v) {
  g[u].push_back(v);
  g[v].push_back(u);
}

void solve() {
  int n, m;
  scanf("%d%d", &n, &m);
  map<int, int> f;
  int id = 1;
  for(int i = 0; i < m; i++) {
    int u, v, c;
    scanf("%d%d%d", &u, &v, &c);
    if(f.find(c) == f.end()) {
      f[c] = id++;
    }
    add(u, n + f[c]);
    add(v, n + f[c]);
  }

  int s, e;
  scanf("%d%d", &s, &e);
  deque<int> q;
  q.push_front(s);
  vector<int> d(n + m + 5, INF);
  d[s] = 0;

  while(q.size() > 0) {
    int u = q.front(); q.pop_front();
    //cout << u << endl;
    for(int v : g[u]) {
      if(1 <= u && u <= n) {
        if(1 + d[u] < d[v]) {
          d[v] = 1 + d[u];
          q.push_back(v);
        }
      } else {
        if(d[u] < d[v]) {
          d[v] = d[u];
          q.push_front(v);
        }
      }
    }
  }

  printf("%d\n", d[e]);
  for(int i = 0; i <= n + m + 5; i++) g[i].clear();
}


int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}

