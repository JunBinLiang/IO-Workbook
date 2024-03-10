#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <set>
#include <string.h>

using namespace std;  
using ll = long long;

const int MOD = 998244353;
void solve() {
  int n, m;
  cin >> n >> m;
  vector<ll> a(n + 1);
  vector<int> in(n + 1), out(n + 1);
  vector<vector<int>> g(n + 1);
  for(int i = 1; i <= n; i++) cin >> a[i];
  for(int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    g[u].push_back(v);
    in[v]++;
    out[u] = 1;
  }

  //simulate the first n round
  for(int i = 1; i <= n; i++) {
    vector<bool> check(n + 1);
    bool finish = true;
    for(int u = 1; u <= n; u++) {
      if(a[u] > 0) {
        a[u]--;
        check[u] = true;
        finish = false;
      }
    }

    if(finish) {
      cout << i - 1 << endl;
      return;
    }
    for(int u = 1; u <= n; u++) {
      if(check[u]) {
        for(int v : g[u]) {
          a[v]++;
        }
      }
    }
  }

  queue<int> q;
  for(int u = 1; u <= n; u++) {
    if(!in[u]) q.push(u);
  }

  while(q.size() > 0) {
    int u = q.front(); q.pop();
    for(int v : g[u]) {
      a[v] += a[u];
      a[v] %= MOD;
      in[v]--;
      if(!in[v]) q.push(v);
    }
  }
  
  for(int u = 1; u <= n; u++) {
    if(!out[u]) {
      cout << (a[u] + n) % MOD << endl;
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

