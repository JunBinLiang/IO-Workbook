//https://vjudge.net/problem/%E6%B4%9B%E8%B0%B7-P5283

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


const int N = 500000 + 1000;

ll a[N];
int b[N];

void mock(int n) {
    vector<ll> b;
    for(int i = 1; i <= n; i++) {
        ll xo = 0;
        for(int j = i; j <= n; j++) {
            xo ^= a[j];
            b.push_back(xo);
        }
    }
    sort(b.begin(), b.end());
    reverse(b.begin(), b.end());
    ll s = 0;
    for(int i = 0; i < b.size(); i++) {
        s += b[i];
        if(i < 10)
            cout << i << "  " << b[i] << " " << s << endl;
    }
    //cout << endl;
}

struct PersistantTrie {
  int roots[N];
  int tr[N * 36][2];
  int sz[N * 36 * 2];
  int id;

  void init() {
    memset(tr, -1, sizeof tr);
    memset(sz, 0, sizeof sz);
    roots[0] = 0;
    id = 1;
  }

  void add(int ith, ll x) {
    roots[ith] = id++;
    int pu = roots[ith - 1], u = roots[ith];
    for(int i = 34; i >= 0; i--) {
      int b = 0;
      if(x & (1ll << i)) b = 1;
      if(pu == -1) {
        tr[u][b] = id++;
        u = tr[u][b];
        sz[u] = 1;
      } else {
        if(tr[pu][b] == -1) {
          tr[u][b] = id++;
          tr[u][b ^ 1] = tr[pu][b ^ 1];
          u = tr[u][b];
          pu = -1;
          sz[u] = 1;
        } else {
          tr[u][b] = id++;
          tr[u][b ^ 1] = tr[pu][b ^ 1];
          u = tr[u][b];
          pu = tr[pu][b];
          sz[u] = 1 + sz[pu];
        }
      }
    }
  }

  ll query(int ith, int k, ll x) {
    int u = roots[ith];
    int size = 0;
    if(tr[u][0] != -1) size += sz[tr[u][0]];
    if(tr[u][1] != -1) size += sz[tr[u][1]];
    if(k > size) return -1;
    
    ll ans = 0;
    for(int i = 34; i >= 0; i--) {
      int b = 0;
      if(x & (1ll << i)) b = 1;
      if(tr[u][b ^ 1] == -1) {
        u = tr[u][b];
      } else {
        if(sz[tr[u][b ^ 1]] >= k) {
          u = tr[u][b ^ 1];
          ans += (1ll << i);
        } else {
          k -= sz[tr[u][b ^ 1]];
          u = tr[u][b];
        }
      }
    }
    return ans;
  } 
} pt;

void solve() {
  int n, k;
  scanf("%d%d", &n, &k);
  for(int i = 1; i <= n; i++) {
    scanf("%lld", &a[i]);
  }
  
  //mock(n);
  
  memset(b, 0, sizeof b);
  priority_queue<pair<ll, int>> pq;
  pt.init(); pt.add(0, 0);
  
  ll xo = 0;
  for(int i = 1; i <= n; i++) {
    xo ^= a[i];
    a[i] = xo;
    pt.add(i, a[i]);
    b[i] = 1;
    pq.push({pt.query(i - 1, 1, a[i]), i});
  }
  
  ll ans = 0;
  for(int i = 0; i < k; i++) {
    pair<ll, int> p = pq.top();
    pq.pop();
    ans += p.first;
    int j = p.second;
    b[j]++;
    ll next = pt.query(j - 1, b[j], a[j]);
    if(next == -1) {
      
    } else {
      pq.push({next, j});
    }
  }
  cout << ans << endl;
}

int main(){
  int t = 1;
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
