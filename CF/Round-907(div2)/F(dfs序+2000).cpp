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

const int SIZE = 5e5 + 100;
struct Fenwick {
  ll tree[SIZE];
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

  ll pre(int i) {
    ll sum = 0;
    while(i>0){
      sum += tree[i];
      i -= ( i & -i);
    }
    return sum;
  }
  ll query(int i, int j) {
      return pre(j + 1) - pre(i);
  }
} tr;

struct Q {
  int op, first, second;
};

const int N = 5e5 + 10;
vector<int> g[N];
int id = 0;
int sz[N], ids[N];

void dfs(int pa, int u) {
  ids[u] = id++;
  sz[u] = 1;
  for(int v : g[u]) {
    if(v == pa) continue;
    dfs(u, v);
    sz[u] += sz[v];
  }
}

void solve() {
  int n;
  scanf("%d", &n);
  for(int i = 0; i <= n; i++) g[i].clear();

  int size = 1;
  id = 0;
  vector<Q> q(n);
  tr.init(n);

  for(int i = 0; i < n; i++) {
    scanf("%d", &q[i].op);
    if(q[i].op == 1) {
      scanf("%d", &q[i].first);
      q[i].second = ++size;
      g[q[i].first].push_back(q[i].second);
      g[q[i].second].push_back(q[i].first);
    } else {
      scanf("%d%d", &q[i].first, &q[i].second);
    }
  }

  dfs(-1, 1);
  vector<ll> ans;
  for(int i = n - 1; i >= 0; i--) {
    if(q[i].op == 1) {
      int u = q[i].second;
      ans.push_back(tr.query(0, ids[u]));
    } else {
      int u = q[i].first, add = q[i].second;
      int l = ids[u], r = l + sz[u] - 1;
      tr.update(l, add);
      tr.update(r + 1, -add);
    }
  } 
  //add the root
  ans.push_back(tr.query(0, ids[1]));

  reverse(ans.begin(), ans.end());
  for(int i = 0; i < ans.size(); i++) {
    printf("%lld ", ans[i]);
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
