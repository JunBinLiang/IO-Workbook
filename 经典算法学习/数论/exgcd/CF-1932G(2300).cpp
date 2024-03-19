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
#define FOR(i, a, b) for (int i = a; i < b; ++i)

const int N = 1e5 + 100;
const ll INF = 1e18;
ll dist[N];
int l[N], s[N];
bool st[N];
vector<int> g[N];

int n, m, h;

ll exgcd(ll a, ll b, ll &x, ll &y)
{
  if(b==0) {
    x = 1;
    y = 0;
    return a;
  }
  int r = exgcd(b, a%b, x, y);
  int t = y;
  y = x - (a / b) * y;
  x = t;
  return r;
}

void dijkstra() {
  for(int i = 0; i <= n; i++) {
    dist[i] = INF;
    st[i] = 0;
  }
  
  dist[1] = 0;
  priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> heap;
  heap.push({0ll, 1});

  while (heap.size()) {
    auto t = heap.top();
    heap.pop();
    int u = t.second;
    if (st[u]) continue;
    st[u] = true;
    
    for(int v : g[u]) {
      int c = ((l[u] - l[v]) + h) % h;
      int a = ((s[v] - s[u]) + h) % h;



      int b = h;
      if(c % __gcd(a, b) != 0) continue;
      ll x, y;
      exgcd(a, b, x, y);
      
      int gcd = __gcd(a, h);
      x = (x * (c / gcd)) % h;//计算原方程解
      int bt = b / gcd;
      x = (x % bt + bt) % bt; // 求出最小非负整数解
      if(x < dist[u]) {
        ll cnt = (dist[u] - x) / bt;
        if((dist[u] - x) % bt != 0) cnt++;
        x += cnt * bt;
      }
      
      //cout << "next " << u << " " << v << " " << x << endl;
      //cout << a << " " << b << " " << c << endl;
      
      if(x + 1 < dist[v]) {
        dist[v] = x + 1;
        heap.push({dist[v], v});
      }
    }
  }
}

//扩展欧几里得 : https://www.cnblogs.com/fusiwei/p/11775503.html
void solve() {
  scanf("%d%d%d", &n, &m, &h);

  for(int i = 0; i <= n; i++) g[i].clear();
  for(int i = 1; i <= n; i++) {
    scanf("%d", &l[i]);
  }
  for(int i = 1; i <= n; i++) {
    scanf("%d", &s[i]);
  }

  for(int i = 0; i < m; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    g[u].push_back(v);
    g[v].push_back(u);
  }

  dijkstra();
  if(dist[n] == INF) {
    printf("-1\n");
  } else {
    printf("%lld\n", dist[n]);
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

