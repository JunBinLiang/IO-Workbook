#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string.h>

using namespace std;  
using ll = long long;

const int N = (1e5 + 10) * 2;
const ll INF = 1e18;
ll a[N], p[N], sum[N], dp[N];

int find(int u) {
  return p[u] == u ? u : p[u] = find(p[u]);
}

struct E {
  int u, v, w;
  bool operator<(const E& other) {
    return w > other.w;
  }
} e[N];

void solve() {
  int n, m;
  cin >> n >> m;
  for(int i = 1; i <= n; i++) {
    scanf("%lld", &a[i]);
  }
  for(int i = 0; i < m; i++) {
    scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
  }
  sort(e, e + m);

  for(int i = 1; i <= n; i++) {
    p[i] = i;
    dp[i] = INF;
    sum[i] = a[i];
  }

  int node = n + 1;
  for(int i = 0; i < m; i++) {
    int u = e[i].u, v = e[i].v, w = e[i].w;
    int r1 = find(u), r2 = find(v);
    if(r1 == r2) continue;
    p[r1] = p[r2] = p[node] = node;
    sum[node] = sum[r1] + sum[r2];
    dp[node] = max(min(w + 0ll, dp[r1]) - sum[r2], min(w + 0ll, dp[r2]) - sum[r1]);
    node++;
  }

  if(dp[node - 1] <= 0) cout << -1 << endl;
  else {
    cout << dp[node - 1] << endl;
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

