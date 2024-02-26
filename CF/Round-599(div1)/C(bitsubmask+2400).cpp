#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <string.h>

using namespace std;  
using ll = long long;


const int N = 20, INF = 2e9;
vector<int> a[N], cycles[(1 << 15) + 10];
ll f[(1 << 15) + 10];
ll s[20], avg;
bool ok[N];
unordered_map<ll, bool> ms[N];
int n;
void dfs(vector<int>& path, vector<int>& dfn, int u, int h, ll x, ll v, int st){
  path.push_back(u);
  dfn[u] = h;
  st += (1 << u);
  
  for(int i = 0; i < n; i++) {
    if(ok[i]) continue;
    if(ms[i].find(s[i] + x - avg) != ms[i].end()) {
      if(dfn[i] == -1) {
        dfs(path, dfn, i, h + 1, s[i] + x - avg, v, st);
      } else if(dfn[i] == 0) {
        
        if(s[path[0]] + x - v == avg && cycles[st].size() == 0) {
          vector<int> c(path.begin(), path.end());
          cycles[st] = c;
          f[st] = v;
        }
      }
    }
  }
  st -= (1 << u);
  path.pop_back();
  dfn[u] = -1;
} 

void solve() {
  memset(s, 0, sizeof s);
  memset(ok, false, sizeof ok);

  scanf("%d", &n);
  ll sum = 0, cnt = 0;
  for(int i = 0; i < n; i++) {
    int m; cin >> m;
    while(m--) {
      int x;
      scanf("%d", &x);
      a[i].push_back(x);
      ms[i][x] = true;
      sum += x;
      s[i] += x;
    }
  }
  
  if(sum % n != 0) {
    cout << "NO" << endl;
    return;
  }

  avg = sum / n;

  for(int i = 0; i < n; i++) {
    if(s[i] == avg) {
      ok[i] = true;
      cycles[1 << i].push_back(i); //self cycle
      f[1 << i] = a[i][0];
    }
  }
  
  vector<int> path;
  vector<int> dfn(n, -1);

  int maxs = 0;
  for(int i = 0; i < n; i++) {
    if(ok[i]) continue;
    for(int x : a[i]) {
      int cur = x;
      dfs(path, dfn, i, 0, x, x, 0);
    }
  }
  
  

  //cout <<"avg " << avg << endl;
  
  //O(3 ^ n)
  vector<bool> dp(1 << n);
  vector<int> p(1 << n);
  dp[0] = true;
  for(int st = 0; st < (1 << n); st++) {
      for (int sub = st; sub; sub = (sub - 1) & st) {
          if(cycles[sub].size() > 0 && dp[st ^ sub]) {
              dp[st] = true;
              p[st] = sub;
          }
      }
  }
  
  if(!dp.back()) {
      cout << "NO" << endl;
      return;
  }
  
  cout << "YES" << endl;
  vector<pair<ll, int>> ans(n);
  int st = (1 << n) - 1;
  while(st != 0) {
      int sub = p[st];
      st ^= sub;
      vector<int>& v = cycles[sub];
      ll x = f[sub];
      for(int i = 0; i < v.size(); i++) {
          int cur = v[i], nxt = v[(i + 1) % v.size()];
          ans[cur] = {x, nxt + 1};
          x = s[nxt] + x - avg;
      }
  }
  
  for(auto pa : ans) {
      printf("%lld %d\n", pa.first, pa.second);
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

