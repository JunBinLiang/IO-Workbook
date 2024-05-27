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
const int INF = 1e8;
vector<int> g[N];
string s;

int dp[N][3]; 
//0 : no P and S
//1 : only P
//2 : only S

//P ans S can not on the same component
int cal(vector<pair<int, int>>& a) {
  int n = a.size();
  vector<int> l(n), r(n);
  int ans = INF;
  int s = 0;
  for(int i = 0; i < n; i++) {
    s += min(a[i].first, a[i].second);
    l[i] = s;
  }
  s = 0;
  for(int i = n - 1; i >= 0; i--) {
    s += min(a[i].first, a[i].second);
    r[i] = s;
  }
  for(int i = 0; i < n; i++) {
    int v = a[i].second;
    if(i > 0) v += l[i - 1];
    if(i + 1 < n) v += r[i + 1];
    ans = min(ans, v);
  }
  return ans;
}



void dfs(int pa, int u) {
  if(g[u].size() == 1 && u != 1) {
    if(s[u - 1] == 'P') {
      dp[u][1] = 0;
      dp[u][0] = 1; //cut
    } else if(s[u - 1] == 'S') {
      dp[u][2] = 0;
      dp[u][0] = 1; //cut
    } else {
      dp[u][0] = 0;
    }
    return;
  }

  if(s[u - 1] == 'P') {
    dp[u][1] = 0;
  } else if(s[u - 1] == 'S') {
    dp[u][2] = 0;
  } else {
    dp[u][0] = dp[u][1] = dp[u][2] = 0;
  }

  vector<pair<int, int>> a, b;
  for(int v : g[u]) {
    if(v == pa) continue;
    dfs(u, v);
    if(s[u - 1] == 'P') {
      dp[u][1] += min(dp[v][0], dp[v][1]);
    } else if(s[u - 1] == 'S') {
      dp[u][2] += min(dp[v][0], dp[v][2]);
    } else {
      dp[u][0] += dp[v][0];
      a.push_back({dp[v][0], dp[v][1]});
      b.push_back({dp[v][0], dp[v][2]});
    }
  }

  if(s[u - 1] == 'C') {
    dp[u][1] = cal(a);
    dp[u][2] = cal(b);
  }
  
  dp[u][0] = min(dp[u][0], 1 + min(dp[u][1], dp[u][2]));
  //for(auto p : a) cout << p.first << " " << p.second << endl;
  //cout << endl;
  //cout << u << ":   "  << dp[u][0] << " " << dp[u][1] << " " << dp[u][2] << endl;
}

void solve() {
  int n;
  cin >> n;
  for(int i = 0; i <= n; i++) {
    g[i].clear();
    dp[i][0] = dp[i][1] = dp[i][2] = INF;
  }

  for(int i = 2; i <= n; i++) {
    int u;
    cin >> u;
    g[u].push_back(i);
    g[i].push_back(u);
  }

  cin >> s;
  dfs(-1, 1);

  cout << min(dp[1][0], min(dp[1][1], dp[1][2])) << endl;
}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
