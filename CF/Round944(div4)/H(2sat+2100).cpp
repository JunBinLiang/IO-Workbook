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


int n, m;
const int N = 2000010;
const int M = 2000010;
int h[N], e[M], ne[M];
int dfn[N], low[N], id[N];
bool is[N];
int sta[N];

int t = 1;
int idx = 0;
int scc = 0;
int cnt = 0;

void tarjan(int u) {
  dfn[u] = low[u] = t++;
  sta[++idx] = u, is[u] = true;
  for(int i = h[u]; ~i; i = ne[i]) {
    int nxt = e[i];
    if(!dfn[nxt]) {
      tarjan(nxt);
      low[u] = min(low[u], low[nxt]);
    } else if(is[nxt]) {
      low[u] = min(low[u], dfn[nxt]);
    }
  }
  
  if (low[u] == dfn[u]) {
    int y;
    scc ++ ;
    do {
      y = sta[idx -- ], is[y] = false, id[y] = scc;
    } while (y != u);
  }
}

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}


int ID(int x) {
    if(x > 0) return x * 2;
    else return (-x) * 2 + 1;
}

void solve() {
  int n;
  cin >> n;
  vector<vector<int>> g(3, vector<int>(n));
  for(int i = 0; i < 3; i++) {
    for(int j = 0; j < n; j++) {
      cin >> g[i][j];
    }
  }

  //(x, y, z) at least two are true
  for(int i = 0; i <= 2 * n + 10; i++) h[i] = -1, dfn[i] = 0, id[i] = 0;
  idx = 0;
  scc = 0;
  cnt = 0;

  
  for(int i = 0; i < n; i++) {
    int x = g[0][i], y = g[1][i], z = g[2][i];
    //!x -> y   !x -> z
    add(ID(-x), ID(y));
    add(ID(-x), ID(z));
    add(ID(-y), ID(x));
    add(ID(-y), ID(z));
    add(ID(-z), ID(x));
    add(ID(-z), ID(y));
  }

  for(int i = 2; i <= 2 * n; i++) {
    if(!dfn[i]) {
      tarjan(i); 
    }
  }

  for(int i = 1; i <= n; i++) {
    if(id[i * 2] == id[i * 2 + 1]) {
      printf("NO \n");
      return;
    }
  }
  printf("YES \n");

}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
